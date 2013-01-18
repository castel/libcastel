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

            inline ModuleBuilder( std::string const & name = "" );

        public:

            inline std::string const & name( void ) const;

            inline ModuleBuilder & name( std::string const & name );

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

            std::string mName;

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

        ModuleBuilder::ModuleBuilder( std::string const & name )
            : mName( name )
            , mGlobals( )
            , mStatements( nullptr )
        {
        }

        std::string const & ModuleBuilder::name( void ) const
        {
            return mName;
        }

        ModuleBuilder & ModuleBuilder::name( std::string const & name )
        {
            mName = name;

            return * this;
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
