#pragma once

#include <llvm/Support/TypeBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include "castel/runtime/Box.hh"
#include "castel/runtime/Function.hh"
#include "castel/runtime/Number.hh"

namespace llvm
{

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Box, XCompile >
    {
        static StructType * get( llvm::LLVMContext & llvmContext ) {
            llvm::Module tempModule( "", llvmContext );
            return tempModule.getTypeByName( "Box" );
        }
    };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Function, XCompile >
    {
        static StructType * get( llvm::LLVMContext & llvmContext ) {
            llvm::Module tempModule( "", llvmContext );
            return tempModule.getTypeByName( "Box" );
        }
    };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Number, XCompile >
    {
        static StructType * get( llvm::LLVMContext & llvmContext ) {
            llvm::Module tempModule( "", llvmContext );
            return tempModule.getTypeByName( "Box" );
        }
    };

}
