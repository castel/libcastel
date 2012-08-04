#pragma once

#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include "castel/engine/Value.hh"

namespace mpllvm
{

    namespace internal
    {

        template < >
        struct TypeResolver< castel::engine::Value > {
            static llvm::StructType * get( llvm::LLVMContext & llvmContext ) {
                llvm::Module tempModule( "", llvmContext );
                return tempModule.getTypeByName( "box" );
            }
        };

    }

}
