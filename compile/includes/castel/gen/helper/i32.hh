#pragma once

#include <llvm/Constants.h>
#include <llvm/LLVMContext.h>
#include <llvm/Type.h>

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
