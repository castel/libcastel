#pragma once

#include <llvm/IRBuilder.h>
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

        class Scope;

        class CodeBuilder
        {

        public:

            inline CodeBuilder( void );

        public:

            inline ast::Statement * statements( void ) const;

            inline CodeBuilder & statements( ast::Statement * statements );

        public:

            void build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        private:

            ast::Statement * mStatements;

        };

    }

}

#include "castel/ast/Statement.hh"
#include "castel/gen/Scope.hh"

namespace castel
{

    namespace gen
    {

        CodeBuilder::CodeBuilder( void )
            : mStatements( nullptr )
        {
        }

        ast::Statement * CodeBuilder::statements( void ) const
        {
            return mStatements;
        }

        CodeBuilder & CodeBuilder::statements( ast::Statement * statement )
        {
            mStatements = statement;

            return * this;
        }

    }

}
