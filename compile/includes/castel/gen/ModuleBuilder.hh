#pragma once

#include <list>
#include <string>

#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

namespace castel
{

    namespace ast
    {

        class Statement;

    }

    namespace gen
    {

        class ModuleBuilder
        {

        public:

            inline ModuleBuilder( void );

        public:

            inline std::list< std::string > const & globals( void ) const;

            inline std::list< std::string > & globals( void );

            inline ModuleBuilder & globals( std::list< std::string > const & globals );

        public:

            inline ast::Statement * statements( void ) const;

            inline ModuleBuilder & statements( ast::Statement * statements );

        public:

            llvm::Module * build( llvm::LLVMContext & context, llvm::Module * module ) const;

        private:

            std::list< std::string > mGlobals;

            ast::Statement * mStatements;

        };

    }

}

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace gen
    {

        ModuleBuilder::ModuleBuilder( void )
            : mGlobals( )
            , mStatements( nullptr )
        {
        }

        std::list< std::string > const & ModuleBuilder::globals( void ) const
        {
            return mGlobals;
        }

        std::list< std::string > & ModuleBuilder::globals( void )
        {
            return mGlobals;
        }

        ModuleBuilder & ModuleBuilder::globals( std::list< std::string > const & globals )
        {
            mGlobals = globals;

            return * this;
        }

        ast::Statement * ModuleBuilder::statements( void ) const
        {
            return mStatements;
        }

        ModuleBuilder & ModuleBuilder::statements( ast::Statement * statements )
        {
            mStatements = statements;

            return * this;
        }

    }

}
