#pragma once

#include <climits>

#include <llvm/Support/TypeBuilder.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>

#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/boxes/List.hh"
#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/Box.hh"

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
    struct TypeBuilder< castel::runtime::boxes::Bool, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::Class, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::Dict, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::Function, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::List, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::Null, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::Number, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::String, XCompile >
        : public castel::utils::BoxTypeBuilder { };

    template < bool XCompile >
    struct TypeBuilder< castel::runtime::boxes::Undefined, XCompile >
        : public castel::utils::BoxTypeBuilder { };

}
