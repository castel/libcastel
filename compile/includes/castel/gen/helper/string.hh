#pragma once

#include <string>

#include <llvm/IRBuilder.h>
#include <llvm/Value.h>

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
