#pragma once

#include <string>

#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/expr/literal/Function.hh"

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

            inline ast::expr::literal::Function::Parameter * parameters( void ) const;

            inline FunctionBuilder & parameters( ast::expr::literal::Function::Parameter * parameters );

        public:

            inline ast::Statement * statements( void ) const;

            inline FunctionBuilder & statements( ast::Statement * statements );

        public:

            llvm::Value * build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        private:

            std::string mName;

            bool mUseThis;

            ast::expr::literal::Function::Parameter * mParameters;

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

        ast::expr::literal::Function::Parameter * FunctionBuilder::parameters( void ) const
        {
            return mParameters;
        }

        FunctionBuilder & FunctionBuilder::parameters( ast::expr::literal::Function::Parameter * parameters )
        {
            mParameters = parameters;

            return * this;
        }

        ast::Statement * FunctionBuilder::statements( void ) const
        {
            return mStatements;
        }

        FunctionBuilder & FunctionBuilder::statements( ast::Statement * statements )
        {
            mStatements = statements;

            return * this;
        }

    }

}
