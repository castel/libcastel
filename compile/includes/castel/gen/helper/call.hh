#pragma once

#include <stdexcept>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

namespace castel
{

    namespace gen
    {

        namespace helper
        {

            template < typename... T >
            inline llvm::Value * call( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, llvm::Function * function, T... arguments )
            {
                return irBuilder.CreateCall( function, std::vector< llvm::Value * >( { arguments... } ) );
            }

            template < typename... T >
            inline llvm::Value * call( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, std::string const & name, T... arguments )
            {
                llvm::Function * function = module->getFunction( name );

                if ( function == nullptr )
                    throw std::runtime_error( "Builtin function not found : '" + name + "'" );

                return gen::helper::call( context, module, irBuilder, function, arguments... );
            }

        }

    }

}
