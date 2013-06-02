#pragma once

#include <list>
#include <map>
#include <string>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

namespace castel
{

    namespace ast
    {

        class Statement;

    }

    namespace toolchain
    {

        class Compiler
        {

        public:

            Compiler( void );

        public:

            inline std::list< std::string > const & globals( void ) const;

            inline std::list< std::string > & globals( void );

            inline Compiler & globals( std::list< std::string > const & globals );

        public:

            llvm::Module * build( ast::Statement * statements, std::string const & name = "main" );

        private:

            std::list< std::string > mGlobals;

            llvm::LLVMContext mContext;

        };

    }

}

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace toolchain
    {

        std::list< std::string > const & Compiler::globals( void ) const
        {
            return mGlobals;
        }

        std::list< std::string > & Compiler::globals( void )
        {
            return mGlobals;
        }

        Compiler & Compiler::globals( std::list< std::string > const & globals )
        {
            mGlobals = globals;

            return * this;
        }

    }

}
