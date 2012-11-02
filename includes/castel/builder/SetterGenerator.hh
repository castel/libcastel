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

    }

    namespace builder
    {

        class Context;

        class Scope;

        /**
         * This allows to generate the IR code which will set the value of an expression.
         */

        class SetterGenerator : public ast::tools::Visitor
        {

        public:

            /**
             * Constructs a SetterGenerator instance.
             */

            inline SetterGenerator( builder::Scope & scope );

        public:

            /**
             * @param astExpression AST expression
             * @param llvmValue Value
             *
             * Generates the IR code corresponding to the specified expression, and assigns a value to this expression.
             *
             * If the expression is actually a list of expressions, only the code for the first one will be built.
             */

            inline void run( ast::Expression & astExpression, llvm::Value * llvmValue );

        public:

            /**
             * This method should only be called by instances of ast::expr::Binary.
             */

            virtual void visit( ast::expr::Binary & astBinaryExpression );

            /**
             * This method should only be called by instances of ast::expr::Variable.
             */

            virtual void visit( ast::expr::Variable & astVariableExpression );

        private:

            builder::Context & mContext;

            builder::Scope & mScope;

            llvm::Value * mLLVMValue;

        };

    }

}

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/Expression.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        SetterGenerator::SetterGenerator( builder::Scope & scope )
            : mContext( scope.context( ) )
            , mScope( scope )
        {
        }

        void SetterGenerator::run( ast::Expression & astExpression, llvm::Value * llvmValue )
        {
            mLLVMValue = llvmValue;
            astExpression.accept( * this );
        }

    }

}
