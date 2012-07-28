#pragma once

#include <vector>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
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

            llvm::Value * doubleValue( llvm::Value * source )
            {
                this->forceType< engine::Value::DoubleTy >( source );

                llvm::Value * typecasted = mGenerationEngine.builder( ).CreateBitCast( source, mGenerationEngine.doubleStructPtrType( ) );

                llvm::Value * valueIndex = mGenerationEngine.builder( ).CreateGEP( typecasted, std::vector< llvm::Value * >( {
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 64, 0 ) ),
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, 1 ) ),
                } ) );

                return mGenerationEngine.builder( ).CreateLoad( valueIndex );
            }

        public:

            llvm::Value * boxDouble( double n )
            {
                return this->boxDouble( llvm::ConstantFP::get( mGenerationEngine.context( ), llvm::APFloat( n ) ) );
            }

            llvm::Value * boxDouble( llvm::Value * value )
            {
                llvm::Value * size = mGenerationEngine.builder( ).CreatePtrToInt( mGenerationEngine.builder( ).CreateGEP( llvm::ConstantPointerNull::get( mGenerationEngine.doubleStructPtrType( ) ), std::vector< llvm::Value * >( {
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 64, 1 ) ),
                } ) ), mpllvm::get< int >( mGenerationEngine.context( ) ) );

                llvm::Value * memory = mGenerationEngine.builder( ).CreateCall( mGenerationEngine.module( ).getFunction( "p9_malloc" ), size );
                llvm::Value * box = mGenerationEngine.builder( ).CreateBitCast( memory, mGenerationEngine.doubleStructPtrType( ) );
                llvm::Value * type = llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, engine::Value::DoubleTy ) );

                llvm::Value * typeIndex = mGenerationEngine.builder( ).CreateGEP( box, std::vector< llvm::Value * >( {
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 64, 0 ) ),
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, 0 ) ),
                } ) );

                llvm::Value * valueIndex = mGenerationEngine.builder( ).CreateGEP( box, std::vector< llvm::Value * >( {
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 64, 0 ) ),
                    llvm::ConstantInt::get( mGenerationEngine.context( ), llvm::APInt( 32, 1 ) ),
                } ) );

                mGenerationEngine.builder( ).CreateStore( type, typeIndex );
                mGenerationEngine.builder( ).CreateStore( value, valueIndex );

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
