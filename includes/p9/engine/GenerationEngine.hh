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
                this->initBoxType( );
                this->initFunctionBoxType( );
                this->initDoubleBoxType( );
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

            llvm::Type * boxType( void ) const
            {
                return mBoxType;
            }

            llvm::Type * functionBoxType( void ) const
            {
                return mFunctionBoxType;
            }

            llvm::Type * doubleBoxType( void ) const
            {
                return mDoubleBoxType;
            }

        private:

            void initBoxType( void )
            {
                mBoxType = mpllvm::craft< std::int32_t >( mContext );
            }

            void initFunctionBoxType( void )
            {
                mFunctionBoxType = mpllvm::craft< std::int32_t, std::int32_t, void * >( mContext );
            }

            void initDoubleBoxType( void )
            {
                mDoubleBoxType = mpllvm::craft< std::int32_t, double >( mContext );
            }

        private:

            void initRuntimeFunctions( void )
            {
                llvm::Function::Create( mpllvm::deduce( mContext, & p9Crash ), llvm::GlobalValue::ExternalLinkage, "p9Crash", & mModule );
                llvm::Function::Create( mpllvm::deduce( mContext, & p9Malloc ), llvm::GlobalValue::ExternalLinkage, "p9Malloc", & mModule );
            }

        private:

            llvm::LLVMContext mContext;
            llvm::IRBuilder< > mBuilder;
            llvm::Module mModule;

            llvm::Type * mBoxType;
            llvm::Type * mFunctionBoxType;
            llvm::Type * mDoubleBoxType;

        };

    }

}
