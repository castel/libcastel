#pragma once

#include <string>

#include <llvm/Function.h>

#include "castel/ast/Parameter.hh"
#include "castel/ast/Statement.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        class ClassBuilder;

        /**
         * An helper class building a runtime function box from an AST.
         */

        class FunctionBuilder
        {

            friend builder::ClassBuilder;

        public:

            inline FunctionBuilder( std::string const & name = "", ast::Parameter * parameters = nullptr, ast::Statement * statements = nullptr );

        public:

            /**
             * @return Function name
             */

            inline std::string const & name( void ) const;

            /**
             * @param name Function name
             */

            inline FunctionBuilder & name( std::string const & name );

        public:

            /**
             * @return "Use This" flag
             */

            inline bool useThis( void ) const;

            /**
             * @param useThis "Use This" flag
             */

            inline FunctionBuilder & useThis( bool useThis );

        public:

            /**
             * @return Parameter list
             */

            inline ast::Parameter * parameters( void ) const;

            /**
             * @param parameters Parameter list
             *
             * The parameter list will not be owned by the FunctionBuilder. You have to delete it explicitely
             * when you don't need the FunctionBuilder instance anymore (except if another object is owning the
             * parameter list, such as an AST node).
             */

            inline FunctionBuilder & parameters( ast::Parameter * parameters );

        public:

            /**
             * @return Function statements statement list
             */

            inline ast::Statement * statements( void ) const;

            /**
             * @param statements Function statements statement list
             *
             * The statement list will not be owned by the FunctionBuilder. You have to delete it explicitely
             * when you don't need the FunctionBuilder instance anymore (except if another object is owning the
             * parameter list, such as an AST node).
             */

            inline FunctionBuilder & statements( ast::Statement * statements );

        public:

            /**
             * @param context Related context
             *
             * Compile the AST elements into a llvm value containing a top-level runtime::FunctionBox*.
             */

            inline llvm::Value * create( builder::Context & context ) const;

            /**
             * @param scope Parent scope
             *
             * Compile the AST elements into a llvm value containing a scoped runtime::FunctionBox* (this function
             * will have r/w access on each variable of the parent scopes).
             */

            inline llvm::Value * create( builder::Scope & scope ) const;

        private:

            /**
             * @param context Related context
             * @param scope Parent scope (if applicable)
             *
             * Compile the AST elements into a llvm value containing a runtime::FunctionBox*.
             *
             * @throws std::runtime_error When the scope is not in the specified context.
             */

            llvm::Value * create( builder::Context & context, builder::Scope * scope ) const;

        private:

            std::string mName;
            bool mUseThis;
            ast::Parameter * mParameters;
            ast::Statement * mStatements;

        };

    }

}

#include <string>

#include <llvm/Value.h>

#include "castel/ast/Parameter.hh"
#include "castel/ast/Statement.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        FunctionBuilder::FunctionBuilder( std::string const & name, ast::Parameter * parameters, ast::Statement * statements )
            : mName( name )
            , mUseThis( false )
            , mParameters( parameters )
            , mStatements( statements )
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

        ast::Parameter * FunctionBuilder::parameters( void ) const
        {
            return mParameters;
        }

        FunctionBuilder & FunctionBuilder::parameters( ast::Parameter * parameters )
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

        llvm::Value * FunctionBuilder::create( builder::Context & context ) const
        {
            return this->create( context, nullptr );
        }

        llvm::Value * FunctionBuilder::create( builder::Scope & scope ) const
        {
            return this->create( scope.context( ), & scope );
        }

    }

}
