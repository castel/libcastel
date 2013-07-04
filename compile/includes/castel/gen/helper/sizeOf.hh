#pragma once

#include <cstdint>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

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

                return irBuilder.CreatePtrToInt( irBuilder.CreateConstGEP1_32( nullPointer, 1 ), gen::helper::type< std::int32_t >( context ) );
            }

            template < typename T >
            inline llvm::Value * sizeOf( llvm::LLVMContext & context, llvm::IRBuilder< > & irBuilder )
            {
                return gen::helper::sizeOf( context, irBuilder, gen::helper::type< T >( context ) );
            }

        }

    }

}
