#pragma once

#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include <mpllvm/mpllvm.hh>

#include "castel/engine/Closure.hh"
#include "castel/engine/Box.hh"

namespace castel
{

    namespace engine
    {

        class Closure::Descriptor
        {

        public:

            Descriptor  ( llvm::LLVMContext & llvmContext, engine::Closure::Variable & variable, unsigned int depth               )
            : mDummy    ( new llvm::LoadInst( llvm::ConstantPointerNull::get( mpllvm::get< engine::Box *** >( llvmContext ) ) ) )
            , mVariable ( variable                                                                                                )
            , mDepth    ( depth                                                                                                   )
            {
            }

        public:

            llvm::Value * dummy( void ) const
            {
                return mDummy;
            }

        public:

            engine::Closure::Variable & variable( void ) const
            {
                return mVariable;
            }

        public:

            unsigned int depth( void ) const
            {
                return mDepth;
            }

        private:

            llvm::Value * mDummy;

            engine::Closure::Variable & mVariable;

            unsigned int mDepth;

        };

    }

}
