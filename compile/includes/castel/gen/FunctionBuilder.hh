#pragma once

#include <string>

#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/expr/literal/Function.hh"
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

        class FunctionBuilder
        {

        public:

            inline FunctionBuilder( std::string const & name = "" );

        public:

            inline std::string const & name( void ) const;

            inline FunctionBuilder & name( std::string const & name );

        public:

            inline bool useThis( void ) const;

            inline FunctionBuilder & useThis( bool useThis );

        public:

            inline ast::tools::List< ast::expr::literal::Function::Parameter > const * parameters( void ) const;

            inline FunctionBuilder & parameters( ast::tools::List< ast::expr::literal::Function::Parameter > const * parameters );

        public:

            inline ast::tools::List< ast::Statement > const * statements( void ) const;

            inline FunctionBuilder & statements( ast::tools::List< ast::Statement > const * statements );

        public:

            llvm::Value * build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        private:

            std::string mName;

            bool mUseThis;

            ast::tools::List< ast::expr::literal::Function::Parameter > const * mParameters;

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

        FunctionBuilder::FunctionBuilder( std::string const & name )
            : mName( name )
            , mUseThis( false )
            , mParameters( nullptr )
            , mStatements( nullptr )
        {
        }

        std::string const & FunctionBuilder::name( void ) const
        {
            return mName;
        }

        FunctionBuilder & FunctionBuilder::name( std::string const & name )
        {
            mName = name;

            return * this;
        }

        bool FunctionBuilder::useThis( void ) const
        {
            return mUseThis;
        }

        FunctionBuilder & FunctionBuilder::useThis( bool useThis )
        {
            mUseThis = useThis;

            return * this;
        }

        ast::tools::List< ast::expr::literal::Function::Parameter > const * FunctionBuilder::parameters( void ) const
        {
            return mParameters;
        }

        FunctionBuilder & FunctionBuilder::parameters( ast::tools::List< ast::expr::literal::Function::Parameter > const * parameters )
        {
            mParameters = parameters;

            return * this;
        }

        ast::tools::List< ast::Statement > const * FunctionBuilder::statements( void ) const
        {
            return mStatements;
        }

        FunctionBuilder & FunctionBuilder::statements( ast::tools::List< ast::Statement > const * statements )
        {
            mStatements = statements;

            return * this;
        }

    }

}
