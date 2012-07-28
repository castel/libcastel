#pragma once

#include <vector>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Type.h>
#include <llvm/Value.h>
#include <mpllvm/mpllvm.hh>

#include "p9/engine/GenerationEngine.hh"
#include "p9/engine/Value.hh"
#include <iostream>
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

            llvm::Value * boxToDouble( llvm::Value * genericBox )
            {
                this->forceType< engine::Value::Type::Double >( genericBox );

                llvm::Value * box = mGenerationEngine.builder( ).CreateBitCast( genericBox, mGenerationEngine.doubleStructPtrType( ) );

                llvm::Value * valueIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );

                return mGenerationEngine.builder( ).CreateLoad( valueIndex );
            }

        public:

            llvm::Value * doubleToBox( double n )
            {
                return this->doubleToBox( llvm::ConstantFP::get( mGenerationEngine.context( ), llvm::APFloat( n ) ) );
            }

            llvm::Value * doubleToBox( llvm::Value * value )
            {
                llvm::Value * box = this->allocateObject( mGenerationEngine.doubleStructType( ) );
                llvm::Value * type = llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, static_cast< std::int32_t>( engine::Value::Type::Double ) ) );

                llvm::Value * typeIndex = mpllvm::GEP< 64, 0, 32, 0 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );
                llvm::Value * valueIndex = mpllvm::GEP< 64, 0, 32, 1 >::build( mGenerationEngine.context( ), mGenerationEngine.builder( ), box );

                mGenerationEngine.builder( ).CreateStore( type, typeIndex );
                mGenerationEngine.builder( ).CreateStore( value, valueIndex );

                return this->boxToGeneric( box );
            }

        public:

            llvm::Value * boxToGeneric( llvm::Value * box )
            {
                return mGenerationEngine.builder( ).CreateBitCast( box, mGenerationEngine.valueStructPtrType( ) );
            }

        public:

            template < engine::Value::Type T >
            llvm::Value * forceType( llvm::Value * value )
            {
                /* security check here */

                return value;
            }

        private:

            engine::GenerationEngine & mGenerationEngine;

        };

    }

}
