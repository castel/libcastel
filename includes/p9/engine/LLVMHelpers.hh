#pragma once

#include <cstdint>
#include <vector>

#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Type.h>
#include <llvm/Value.h>
#include <mpllvm/mpllvm.hh>

#include "p9/engine/GenerationEngine.hh"
#include "p9/engine/Value.hh"

namespace p9
{

    namespace engine
    {

        class LLVMHelpers
        {

        public:

            LLVMHelpers         ( engine::GenerationEngine & generationEngine )
            : mGenerationEngine ( generationEngine )
            {
            }

        public:

            llvm::Value * sizeOf( llvm::Type * type )
            {
                llvm::Type * targetType = llvm::IntegerType::get( mGenerationEngine.context( ), 32 );
                llvm::ConstantPointerNull * nullPointer = llvm::ConstantPointerNull::get( llvm::PointerType::get( type, 0 ) );
                return mGenerationEngine.builder( ).CreatePtrToInt( mpllvm::GEP< 64, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), nullPointer ), targetType );
            }

            llvm::Value * allocateObject( llvm::Type * type )
            {
                llvm::Function * p9Malloc = mGenerationEngine.module( ).getFunction( "p9Malloc" );
                llvm::Value * memoryAddress = mGenerationEngine.builder( ).CreateCall( p9Malloc, this->sizeOf( type ) );
                return mGenerationEngine.builder( ).CreateBitCast( memoryAddress, llvm::PointerType::get( type, 0 ) );
            }

        public:

            llvm::Function * boxToFunction( llvm::Value * genericBox, std::int32_t arity )
            {
                this->forceBoxType< engine::Value::Type::Function >( genericBox );

                llvm::Value * box = mGenerationEngine.builder( ).CreateBitCast( genericBox, llvm::PointerType::get( mGenerationEngine.functionBoxType( ), 0 ) );

                llvm::Value * arityIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );
                llvm::Value * functionArity = mGenerationEngine.builder( ).CreateLoad( arityIndex );
                llvm::Value * expectedArity = llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, arity ) );
                llvm::Value * arityCheck = mGenerationEngine.builder( ).CreateICmpNE( functionArity, expectedArity );

                llvm::Function * outerFunction = mGenerationEngine.builder( ).GetInsertBlock( )->getParent( );

                llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "then", outerFunction );
                llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "finally" );

                llvm::Value * conditionalBranching = mGenerationEngine.builder( ).CreateCondBr( arityCheck, thenBranch, finallyBranch );

                mGenerationEngine.builder( ).SetInsertPoint( thenBranch );

                llvm::Function * runtimeP9Crash = mGenerationEngine.module( ).getFunction( "p9Crash" );
                llvm::Value * errorMessage = mGenerationEngine.builder( ).CreateBitCast( llvm::ConstantDataArray::getString( mGenerationEngine.context( ), "Bad argument number in function call" ), mpllvm::get< char const * >( mGenerationEngine.context( ) ) );
                mGenerationEngine.builder( ).CreateCall( runtimeP9Crash, errorMessage );
                mGenerationEngine.builder( ).CreateUnreachable( );

                outerFunction->getBasicBlockList( ).push_back( finallyBranch );

                mGenerationEngine.builder( ).SetInsertPoint( finallyBranch );

                llvm::Type * boxType = llvm::PointerType::get( mGenerationEngine.boxType( ), 0 );
                llvm::FunctionType * functionType = llvm::FunctionType::get( boxType, std::vector< llvm::Type * >( arity, boxType ), false );

                llvm::Value * functionIndex = mpllvm::GEP< 64, 0, 32, 2 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );
                llvm::Value * genericFunction = mGenerationEngine.builder( ).CreateLoad( functionIndex );

                return static_cast< llvm::Function * >( mGenerationEngine.builder( ).CreateBitCast( genericFunction, llvm::PointerType::get( functionType, 0 ) ) );

            }

            llvm::Value * functionToBox( llvm::Function * function )
            {
                llvm::Value * box = this->allocateObject( mGenerationEngine.functionBoxType( ) );

                llvm::Value * typeIndex = mpllvm::GEP< 64, 0, 32, 0 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );
                llvm::Value * arityIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );
                llvm::Value * functionIndex = mpllvm::GEP< 64, 0, 32, 2 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );

                llvm::Value * genericFunction = mGenerationEngine.builder( ).CreateBitCast( function, mpllvm::get< void * >( mGenerationEngine.context( ) ) );

                mGenerationEngine.builder( ).CreateStore( this->boxType< engine::Value::Type::Function >( ), typeIndex );
                mGenerationEngine.builder( ).CreateStore( llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, function->arg_size( ) ) ), arityIndex );
                mGenerationEngine.builder( ).CreateStore( genericFunction, functionIndex );

                return this->boxToGeneric( box );
            }

        public:

            llvm::Value * boxToDouble( llvm::Value * genericBox )
            {
                this->forceBoxType< engine::Value::Type::Double >( genericBox );

                llvm::Value * box = mGenerationEngine.builder( ).CreateBitCast( genericBox, llvm::PointerType::get( mGenerationEngine.doubleBoxType( ), 0 ) );

                llvm::Value * valueIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );

                return mGenerationEngine.builder( ).CreateLoad( valueIndex );
            }

            llvm::Value * doubleToBox( double n )
            {
                return this->doubleToBox( llvm::ConstantFP::get( mGenerationEngine.context( ), llvm::APFloat( n ) ) );
            }

            llvm::Value * doubleToBox( llvm::Value * value )
            {
                llvm::Value * box = this->allocateObject( mGenerationEngine.doubleBoxType( ) );

                llvm::Value * typeIndex = mpllvm::GEP< 64, 0, 32, 0 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );
                llvm::Value * valueIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );

                mGenerationEngine.builder( ).CreateStore( this->boxType< engine::Value::Type::Double >( ), typeIndex );
                mGenerationEngine.builder( ).CreateStore( value, valueIndex );

                return this->boxToGeneric( box );
            }

        public:

            llvm::Value * boxToGeneric( llvm::Value * box )
            {
                return mGenerationEngine.builder( ).CreateBitCast( box, llvm::PointerType::get( mGenerationEngine.boxType( ), 0 ) );
            }

        public:

            template < engine::Value::Type Type >
            llvm::Value * boxType( void ) const
            {
                return llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, static_cast< std::int32_t>( Type ) ) );
            }

            template < engine::Value::Type Type >
            llvm::Value * forceBoxType( llvm::Value * value )
            {
                /* security check here */

                return value;
            }

        private:

            engine::GenerationEngine & mGenerationEngine;

        };

    }

}
