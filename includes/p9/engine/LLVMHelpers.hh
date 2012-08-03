#pragma once

#include <cstdint>
#include <vector>

#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/Value.h>
#include <mpllvm/mpllvm.hh>

#include "p9/engine/GenerationEngine.hh"
#include "p9/engine/Value.hh"
#include "p9/utils/mpllvmExtensions.hh"

namespace p9
{

    namespace engine
    {

        class LLVMHelpers
        {

        public:

            LLVMHelpers    ( llvm::LLVMContext & llvmLLVMContext, llvm::IRBuilder< > & irBuilder, llvm::Module & module )
            : mLLVMContext ( llvmLLVMContext )
            , mIRBuilder   ( irBuilder   )
            , mModule      ( module      )
            {
            }

        public:

            llvm::Value * sizeOf( llvm::Type * type )
            {
                /* See here : http://nondot.org/sabre/LLVMNotes/SizeOf-OffsetOf-VariableSizedStructs.txt */
                llvm::Type * targetType = llvm::IntegerType::get( mLLVMContext, 32 );
                llvm::ConstantPointerNull * nullPointer = llvm::ConstantPointerNull::get( llvm::PointerType::get( type, 0 ) );
                return mIRBuilder.CreatePtrToInt( mpllvm::GEP< 64, 1 >::build( mLLVMContext, mIRBuilder, nullPointer ), targetType );
            }

            llvm::Value * allocateObject( llvm::Type * type, int allocateOnTheStack = false )
            {
                if ( allocateOnTheStack ) {
                    /* Allocating on the stack using Alloca */
                    return mIRBuilder.CreateAlloca( type );
                } else {
                    /* Allocating using the heap allocation function */
                    llvm::Function * p9Malloc = mModule.getFunction( "p9Malloc" );
                    llvm::Value * raw = mIRBuilder.CreateCall( p9Malloc, this->sizeOf( type ) );

                    /* Casting the result to get the right result type */
                    return mIRBuilder.CreateBitCast( raw, llvm::PointerType::getUnqual( type ) );
                }
            }

            llvm::Value * allocateArray( llvm::Type * type, int count, int allocateOnTheStack = false )
            {
                /* Crafts the array type */
                llvm::Type * arrayType = llvm::ArrayType::get( type, count );

                /* Allocates memory for multiple objects */
                llvm::Value * array = this->allocateObject( arrayType, allocateOnTheStack );

                /* Casts this array reference into a pointer */
                return array;
                return mpllvm::GEP< 64, 0, 32, 0 >::build( mLLVMContext, mIRBuilder, array );
            }

        public:

            llvm::Function * boxToFunction( llvm::Value * genericBox, std::int32_t arity )
            {
                /* Ensures that the generic dynamic box is really a function */
                this->forceBoxType< engine::Value::Type::Function >( genericBox );

                /* Casts the generic dynamic box into a Function box */
                llvm::Value * functionBox = mIRBuilder.CreateBitCast( genericBox, llvm::PointerType::getUnqual( mModule.getTypeByName( "box.function" ) ) );

                /**** START : checks function arity ****/
                llvm::Value * arityIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mLLVMContext, mIRBuilder, functionBox );
                llvm::Value * functionArity = mIRBuilder.CreateLoad( arityIndex );
                llvm::Value * expectedArity = llvm::ConstantInt::get( mLLVMContext, llvm::APInt( 32, arity ) );
                llvm::Value * arityCheck = mIRBuilder.CreateICmpNE( functionArity, expectedArity );

                llvm::Function * outerFunction = mIRBuilder.GetInsertBlock( )->getParent( );

                llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mLLVMContext, "then", outerFunction );
                llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mLLVMContext, "finally" );

                llvm::Value * conditionalBranching = mIRBuilder.CreateCondBr( arityCheck, thenBranch, finallyBranch );

                mIRBuilder.SetInsertPoint( thenBranch );

                llvm::Function * runtimeP9Crash = mModule.getFunction( "p9Crash" );
                llvm::Value * errorMessage = mpllvm::GEP< 64, 0 >::build( mLLVMContext, mIRBuilder, llvm::ConstantPointerNull::get( mpllvm::get< char const * >( mLLVMContext ) ) );
                mIRBuilder.CreateCall( runtimeP9Crash, errorMessage );
                mIRBuilder.CreateUnreachable( );

                outerFunction->getBasicBlockList( ).push_back( finallyBranch );

                mIRBuilder.SetInsertPoint( finallyBranch );
                /**** END : checks function arity ****/

                /**** START : crafts function type ****/
                llvm::Type * boxType = llvm::PointerType::getUnqual( mModule.getTypeByName( "box" ) );
                llvm::Type * environmentType = llvm::PointerType::getUnqual( llvm::PointerType::getUnqual( llvm::PointerType::getUnqual( boxType ) ) );

                std::vector< llvm::Type * > argumentsTypes( arity + 1, boxType );
                argumentsTypes[ 0 ] = environmentType;

                llvm::FunctionType * functionType = llvm::FunctionType::get( boxType, argumentsTypes, false );
                /**** END : crafts function type ****/

                /* Loads the LLVM function pointer (as void*) */
                llvm::Value * functionIndex = mpllvm::GEP< 64, 0, 32, 2 >::build( mLLVMContext, mIRBuilder, functionBox );
                llvm::Value * genericFunctionPointer = mIRBuilder.CreateLoad( functionIndex );

                /* Casts the function pointer from void* to an LLVM function pointer */
                return static_cast< llvm::Function * >( mIRBuilder.CreateBitCast( genericFunctionPointer, llvm::PointerType::getUnqual( functionType ) ) );

            }

            llvm::Value * functionToBox( llvm::Function * llvmFunction, llvm::Value * environment = nullptr )
            {
                /* Sets a default (empty) environment unless specified */
                if ( environment == nullptr )
                    llvm::ConstantPointerNull::get( mpllvm::get< engine::Value *** >( mLLVMContext ) );

                /* Allocates enough memory for the new box */
                llvm::Value * functionBox = this->allocateObject( mModule.getTypeByName( "box.function" ) );

                /* Compute fields indexes */
                llvm::Value * typeIndex = mpllvm::GEP< 64, 0, 32, 0 >::build( mLLVMContext, mIRBuilder, functionBox );
                llvm::Value * arityIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mLLVMContext, mIRBuilder, functionBox );
                llvm::Value * functionIndex = mpllvm::GEP< 64, 0, 32, 2 >::build( mLLVMContext, mIRBuilder, functionBox );
                llvm::Value * environmentIndex = mpllvm::GEP< 64, 0, 32, 3 >::build( mLLVMContext, mIRBuilder, functionBox );

                /* Casts the function pointer from an LLVM function pointer to void* */
                llvm::Value * genericFunctionPointer = mIRBuilder.CreateBitCast( llvmFunction, mpllvm::get< void * >( mLLVMContext ) );

                /* Populate box data */
                mIRBuilder.CreateStore( this->boxType< engine::Value::Type::Function >( ), typeIndex );
                mIRBuilder.CreateStore( llvm::ConstantInt::get( mLLVMContext, llvm::APInt( 32, llvmFunction->arg_size( ) - 1 ) ), arityIndex );
                mIRBuilder.CreateStore( genericFunctionPointer, functionIndex );
                //mIRBuilder.CreateStore( environment, environmentIndex );

                /* Casts the function box into a generic dynamic box */
                return this->boxToGeneric( functionBox );
            }

            llvm::Value * callFunctionBox( llvm::Value * genericBox, std::vector< llvm::Value * > const & arguments )
            {
                /* Tries to load the inner function */
                llvm::Function * llvmFunction = this->boxToFunction( genericBox, arguments.size( ) );

                /* Casts the generic dynamic box into a Function box */
                llvm::Value * functionBox = mIRBuilder.CreateBitCast( genericBox, llvm::PointerType::getUnqual( mModule.getTypeByName( "box.function" ) ) );

                /* Computes environment field index */
                llvm::Value * environmentIndex = mpllvm::GEP< 64, 0, 32, 3 >::build( mLLVMContext, mIRBuilder, functionBox );

                /* Loads environment */
                llvm::Value * environment = mIRBuilder.CreateLoad( environmentIndex );

                /* Duplicates the arguments and adds the environment at the front */
                std::vector< llvm::Value * > duplicatedArguments;
                duplicatedArguments.push_back( mIRBuilder.CreateBitCast( environment, mpllvm::get< engine::Value **** >( mLLVMContext ) ) );
                duplicatedArguments.insert( duplicatedArguments.end( ), arguments.begin( ), arguments.end( ) );

                /* Finally returns the call */
                return mIRBuilder.CreateCall( llvmFunction, duplicatedArguments );
            }

        public:

            llvm::Value * boxToDouble( llvm::Value * genericBox )
            {
                /* Ensures that the generic dynamic box is really a function */
                this->forceBoxType< engine::Value::Type::Double >( genericBox );

                /* Casts the generic dynamic box into a Double box */
                llvm::Value * doubleBox = mIRBuilder.CreateBitCast( genericBox, llvm::PointerType::getUnqual( mModule.getTypeByName( "box.double" ) ) );

                /* Loads and returns the internal value */
                llvm::Value * valueIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mLLVMContext, mIRBuilder, doubleBox );
                return mIRBuilder.CreateLoad( valueIndex );
            }

            llvm::Value * doubleToBox( double n )
            {
                /* We just forward this action to the master helper */
                return this->doubleToBox( llvm::ConstantFP::get( mLLVMContext, llvm::APFloat( n ) ) );
            }

            llvm::Value * doubleToBox( llvm::Value * value )
            {
                /* Allocates enough memory for the new box */
                llvm::Value * doubleBox = this->allocateObject( mModule.getTypeByName( "box.double" ) );

                /* Compute fields indexes */
                llvm::Value * typeIndex = mpllvm::GEP< 64, 0, 32, 0 >::build( mLLVMContext, mIRBuilder, doubleBox );
                llvm::Value * valueIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mLLVMContext, mIRBuilder, doubleBox );

                /* Populate box data */
                mIRBuilder.CreateStore( this->boxType< engine::Value::Type::Double >( ), typeIndex );
                mIRBuilder.CreateStore( value, valueIndex );

                /* Casts the double box into a generic dynamic box */
                return this->boxToGeneric( doubleBox );
            }

        public:

            llvm::Value * boxToGeneric( llvm::Value * box )
            {
                /* Casts the input box into a generic dynamic box. It does no check on the input */
                return mIRBuilder.CreateBitCast( box, llvm::PointerType::getUnqual( mModule.getTypeByName( "box" ) ) );
            }

        public:

            template < engine::Value::Type Type >
            llvm::Value * boxType( void ) const
            {
                /* Return an integer LLVM value containing the template parameter box type */
                return llvm::ConstantInt::get( mLLVMContext, llvm::APInt( 32, static_cast< std::int32_t>( Type ) ) );
            }

            template < engine::Value::Type Type >
            llvm::Value * forceBoxType( llvm::Value * value )
            {
                /* security check here */

                return value;
            }

        private:

            llvm::LLVMContext & mLLVMContext;
            llvm::IRBuilder< > & mIRBuilder;
            llvm::Module & mModule;

        };

    }

}
