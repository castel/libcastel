#pragma once

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include "castel/gen/helper/type.hh"

namespace castel
{

    namespace gen
    {

        namespace helper
        {

            inline llvm::ConstantPointerNull * null( llvm::PointerType * type )
            {
                return llvm::ConstantPointerNull::get( type );
            }

            template < typename T >
            inline llvm::ConstantPointerNull * null( llvm::LLVMContext & context )
            {
                return gen::helper::null( gen::helper::type< T >( context ) );
            }

        }

    }

}
