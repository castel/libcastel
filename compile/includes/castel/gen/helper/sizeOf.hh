#pragma once

#include <cstdint>

#include <llvm/IRBuilder.h>
#include <llvm/TypeBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/gen/helper/null.hh"
#include "castel/gen/helper/type.hh"

namespace castel
{

    namespace gen
    {

        namespace helper
        {

            inline llvm::Value * sizeOf( llvm::LLVMContext & context, llvm::IRBuilder< > & irBuilder, llvm::Type * type )
            {
                llvm::ConstantPointerNull * nullPointer = gen::helper::null( llvm::PointerType::getUnqual( type ) );

                return irBuilder.CreatePtrToInt( irBuilder.CreateConstGEP1_32( nullPointer, 1 ), gen::helper::type< std::int64_t >( context ) );
            }

            template < typename T >
            inline llvm::Value * sizeOf( llvm::LLVMContext & context, llvm::IRBuilder< > & irBuilder )
            {
                return gen::helper::sizeOf( context, irBuilder, gen::helper::type< T >( context ) );
            }

        }

    }

}
