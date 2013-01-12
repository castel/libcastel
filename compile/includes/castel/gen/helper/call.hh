#pragma once

#include <stdexcept>
#include <string>

#include <llvm/IRBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

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
