#pragma once

#include <llvm/IRBuilder.h>
#include <llvm/TypeBuilder.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/Value.h>

#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/sizeOf.hh"
#include "castel/gen/helper/type.hh"

namespace castel
{

    namespace gen
    {

        namespace helper
        {

            inline llvm::Value * allocate( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, llvm::Type * type, llvm::Value * count, bool onTheStack = false )
            {
                if ( onTheStack )
                    return irBuilder.CreateAlloca( type, count );

                llvm::Value * size = gen::helper::sizeOf( context, irBuilder, type );
                llvm::Value * raw = gen::helper::call( context, module, irBuilder, "Castel_malloc", size, count );

                return irBuilder.CreateBitCast( raw, llvm::PointerType::getUnqual( type ) );
            }

            inline llvm::Value * allocate( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, llvm::Type * type, unsigned int count, bool onTheStack = false )
            {
                return gen::helper::allocate( context, module, irBuilder, type, llvm::ConstantInt::get( context, llvm::APInt( 32, count ) ), onTheStack );
            }

            template < typename T >
            inline llvm::Value * allocate( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, llvm::Value * count, bool onTheStack = false )
            {
                return gen::helper::allocate( context, module, irBuilder, gen::helper::type< T >( context ), count, onTheStack );
            }

            template < typename T >
            inline llvm::Value * allocate( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, unsigned int count, bool onTheStack = false )
            {
                return gen::helper::allocate( context, module, irBuilder, gen::helper::type< T >( context ), count, onTheStack );
            }

        }

    }

}
