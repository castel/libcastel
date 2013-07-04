#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "castel/ast/tools/List.hh"

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

            inline ast::tools::List< ast::Statement > const * statements( void ) const;

            inline CodeBuilder & statements( ast::tools::List< ast::Statement > const * statements );

        public:

            void build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        private:

            ast::tools::List< ast::Statement > const * mStatements;

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

        ast::tools::List< ast::Statement > const * CodeBuilder::statements( void ) const
        {
            return mStatements;
        }

        CodeBuilder & CodeBuilder::statements( ast::tools::List< ast::Statement > const * statement )
        {
            mStatements = statement;

            return * this;
        }

    }

}
