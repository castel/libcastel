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

#include "castel/engine/Value.hh"
#include "castel/runtime/library.hh"

namespace castel
{

    namespace engine
    {

        class GenerationEngine
        {

        public:

            GenerationEngine ( std::string const & name )
            : mLLVMContext   (                    )
            , mIRBuilder     ( mLLVMContext       )
            , mModule        ( name, mLLVMContext )
            {
                this->initTypes( );
                this->initFunctions( );
            }

        public:

            llvm::LLVMContext & llvmContext( void )
            {
                return mLLVMContext;
            }

            llvm::IRBuilder< > & irBuilder( void )
            {
                return mIRBuilder;
            }

            llvm::Module & module( void )
            {
                return mModule;
            }

        private:

            void initTypes( void )
            {
                mpllvm::structure::create< std::int32_t >( mLLVMContext, "box" );
                mpllvm::structure::create< std::int32_t, std::int32_t, void *, engine::Value *** >( mLLVMContext, "box.function" );
                mpllvm::structure::create< std::int32_t, double >( mLLVMContext, "box.double" );
            }

            void initFunctions( void )
            {
                mpllvm::function::create( mLLVMContext, "castelMalloc", & castelMalloc, llvm::GlobalValue::ExternalLinkage, & mModule );
                mpllvm::function::create( mLLVMContext, "castelCrash", & castelCrash, llvm::GlobalValue::ExternalLinkage, & mModule );
            }

        private:

            llvm::LLVMContext mLLVMContext;
            llvm::IRBuilder< > mIRBuilder;
            llvm::Module mModule;

            llvm::Type * mBoxType;
            llvm::Type * mFunctionBoxType;
            llvm::Type * mDoubleBoxType;

        };

    }

}
