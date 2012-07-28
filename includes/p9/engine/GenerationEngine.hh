#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <llvm/Support/IRBuilder.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <mpllvm/mpllvm.hh>

#include "p9/runtime/library.hh"

namespace p9
{

    namespace engine
    {

        class GenerationEngine
        {

        public:

            GenerationEngine ( std::string const & name )
            : mContext       (                )
            , mBuilder       ( mContext       )
            , mModule        ( name, mContext )
            {
                this->initValueStructType( );
                this->initDoubleStructType( );
                this->initRuntimeFunctions( );
            }

        public:

            llvm::LLVMContext & context( void )
            {
                return mContext;
            }

            llvm::IRBuilder< > & builder( void )
            {
                return mBuilder;
            }

            llvm::Module & module( void )
            {
                return mModule;
            }

        public:

            llvm::Type * valueStructType( void ) const
            {
                return mValueStructType;
            }

            llvm::PointerType * valueStructPtrType( void ) const
            {
                return llvm::PointerType::get( mValueStructType, 0 );
            }

        public:

            llvm::Type * doubleStructType( void ) const
            {
                return mDoubleStructType;
            }

            llvm::PointerType * doubleStructPtrType( void ) const
            {
                return llvm::PointerType::get( mDoubleStructType, 0 );
            }

        private:

            void initValueStructType( void )
            {
                mValueStructType = mpllvm::craft< std::int32_t >( mContext );
            }

            void initDoubleStructType( void )
            {
                mDoubleStructType = mpllvm::craft< std::int32_t, double >( mContext );
            }

        private:

            void initRuntimeFunctions( void )
            {
                llvm::Function::Create( mpllvm::deduce( mContext, & p9_malloc ), llvm::GlobalValue::ExternalLinkage, "p9_malloc", & mModule );
            }

        private:

            llvm::LLVMContext mContext;
            llvm::IRBuilder< > mBuilder;
            llvm::Module mModule;

            llvm::Type * mValueStructType;
            llvm::Type * mDoubleStructType;

        };

    }

}
