#pragma once

#include <memory>

#include <llvm/Value.h>

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Binary;
            class Variable;

        }

        class Expression;
        class Token;

    }

    namespace builder
    {

        class Context;
        class Scope;

        class SetterGenerator : public ast::tools::Visitor
        {

        public:

            /**
             * Constructs a SetterGenerator instance.
             */

            inline SetterGenerator( builder::Context & context, builder::Scope & scope );

        public:

            /**
             * Return a LLVM value resulting from the specified AST evaluation.
             */

            inline llvm::Value * expression( ast::Expression & astExpression, llvm::Value * value );

        public:

            virtual void visit( ast::expr::Binary & astBinaryExpression );
            virtual void visit( ast::expr::Variable & astVariableExpression );

        protected:

            virtual void defaultAction( ast::Token & astToken );

        private:

            builder::Context & mContext;
            builder::Scope & mScope;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/Expression.hh"
#include "castel/ast/Token.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        SetterGenerator::SetterGenerator( builder::Context & context, builder::Scope & scope )
            : mContext( context )
            , mScope( scope )
        {
        }

        llvm::Value * SetterGenerator::expression( ast::Expression & astExpression, llvm::Value * value )
        {
            mValue.reset( value );

            astExpression.accept( * this );
            return mValue.release( );
        }

    }

}
