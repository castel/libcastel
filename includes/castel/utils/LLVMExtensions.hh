#pragma once

#include <llvm/Support/TypeBuilder.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>

#include "castel/runtime/Box.hh"
#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Function.hh"
#include "castel/runtime/Number.hh"

namespace castel
{

    namespace utils
    {

        struct BoxTypeBuilder
        {
            static llvm::StructType * get( llvm::LLVMContext & llvmContext ) {
                llvm::Module tempModule( "", llvmContext );
                return tempModule.getTypeByName( "Box" );
            }
        };

    }

}

namespace llvm
{

    template <>
    struct TypeBuilder< bool, false > {
        static llvm::Type * get( llvm::LLVMContext & llvmContext ) {
            return llvm::Type::getInt1Ty( llvmContext );
        }
    };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Box, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Boolean, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Function, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::Number, XCompile >
        : public castel::utils::BoxTypeBuilder { };

}
