#pragma once

#include <string>

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

            inline ast::Statement * statements( void ) const;

            inline ModuleBuilder & statements( ast::Statement * statements );

        public:

            llvm::Module * build( llvm::LLVMContext & context, llvm::Module * module ) const;

        private:

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
            : mStatements( nullptr )
        {
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
