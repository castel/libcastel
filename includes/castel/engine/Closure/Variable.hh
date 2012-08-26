#pragma once

#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/LLVMContext.h>
#include <mpllvm/mpllvm.hh>

#include "castel/engine/Closure.hh"

namespace castel
{

    namespace engine
    {

        class Closure::Variable
        {

        public:

            Variable  ( llvm::LLVMContext & llvmContext, bool escape                                                )
            : mDummy  ( new llvm::LoadInst( llvm::ConstantPointerNull::get( mpllvm::get< int * >( llvmContext ) ) ) )
            , mEscape ( escape                                                                                      )
            {
            }

        public:

            llvm::Value * dummy( void ) const
            {
                return mDummy;
            }

        public:

            bool escape( void ) const
            {
                return mEscape;
            }

            Variable & escape( bool escape )
            {
                mEscape = escape;

                return * this;
            }

        private:

            llvm::Value * mDummy;

            bool mEscape;

        };

    }

}
