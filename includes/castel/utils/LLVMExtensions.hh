#pragma once

#include <llvm/Support/TypeBuilder.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>

#include "castel/runtime/Box.hh"
#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/DictBox.hh"
#include "castel/runtime/FunctionBox.hh"
#include "castel/runtime/ListBox.hh"
#include "castel/runtime/NullBox.hh"
#include "castel/runtime/NumberBox.hh"
#include "castel/runtime/StringBox.hh"
#include "castel/runtime/UndefinedBox.hh"

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
    struct TypeBuilder< castel::runtime::BooleanBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::DictBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::FunctionBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::ListBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::NullBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::NumberBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::StringBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::UndefinedBox, XCompile >
        : public castel::utils::BoxTypeBuilder { };

}
