#pragma once

#include <list>
#include <string>

#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

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

            inline ast::tools::List< ast::Statement > const * statements( void ) const;

            inline ModuleBuilder & statements( ast::tools::List< ast::Statement > const * statements );

        public:

            llvm::Module * build( llvm::LLVMContext & context, llvm::Module * module ) const;

        private:

            std::string mName;

            std::list< std::string > mGlobals;

            ast::tools::List< ast::Statement > const * mStatements;

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

        ast::tools::List< ast::Statement > const * ModuleBuilder::statements( void ) const
        {
            return mStatements;
        }

        ModuleBuilder & ModuleBuilder::statements( ast::tools::List< ast::Statement > const * statements )
        {
            mStatements = statements;

            return * this;
        }

    }

}
