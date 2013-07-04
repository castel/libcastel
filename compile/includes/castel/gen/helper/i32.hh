#pragma once

#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

namespace castel
{

    namespace gen
    {

        namespace helper
        {

            inline llvm::Value * i32( llvm::LLVMContext & context, int n )
            {
                return llvm::ConstantInt::get( context, llvm::APInt( 32, n ) );
            }

        }

    }

}
