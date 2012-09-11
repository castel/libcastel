#pragma once

#include <llvm/Support/TypeBuilder.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include "castel/builder/Closure.hh"
#include "castel/runtime/Box.hh"
#include "castel/utils/LLVMExtensions.hh"

namespace castel
{

    namespace builder
    {

        class Closure::Descriptor
        {

        public:

            Descriptor  ( llvm::LLVMContext & llvmContext, builder::Closure::Variable & variable, unsigned int depth                               )
            : mDummy    ( new llvm::LoadInst( llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box ***, false >::get( llvmContext ) ) ) )
            , mVariable ( variable                                                                                                                 )
            , mDepth    ( depth                                                                                                                    )
            {
            }

        public:

            llvm::Value * dummy( void ) const
            {
                return mDummy;
            }

        public:

            builder::Closure::Variable & variable( void ) const
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

            builder::Closure::Variable & mVariable;

            unsigned int mDepth;

        };

    }

}
