#pragma once

#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

namespace castel
{

    namespace gen
    {

        namespace helper
        {

            inline llvm::Value * string( llvm::IRBuilder< > & irBuilder, std::string const & string )
            {
                return irBuilder.CreateGlobalStringPtr( string );
            }

        }

    }

}
