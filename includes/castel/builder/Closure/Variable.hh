#pragma once

#include <llvm/Support/TypeBuilder.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include "castel/builder/Closure.hh"

namespace castel
{

    namespace builder
    {

        class Closure::Variable
        {

        public:

            Variable  ( llvm::LLVMContext & llvmContext, bool escape                                                                  )
            : mDummy  ( new llvm::LoadInst( llvm::ConstantPointerNull::get( llvm::TypeBuilder< int *, false >::get( llvmContext ) ) ) )
            , mEscape ( escape                                                                                                        )
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
