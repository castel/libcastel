#pragma once

#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include "p9/engine/Value.hh"

namespace mpllvm
{

    namespace internal
    {

        template < >
        struct TypeResolver< p9::engine::Value > {
            static llvm::StructType * get( llvm::LLVMContext & llvmContext ) {
                llvm::Module tempModule( "", llvmContext );
                return tempModule.getTypeByName( "box" );
            }
        };

    }

}
