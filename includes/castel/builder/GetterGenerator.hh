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

            class Bool;

            class Class;

            class Dict;

            class Function;

            class List;

            class Multary;

            class Null;

            class Number;

            class String;

            class Unary;

            class Undefined;

            class Variable;

        }

        class Expression;

    }

    namespace builder
    {

        class Context;

        class Scope;

        /**
         * This class allows to generate the IR code which will get the value of an expression.
         */

        class GetterGenerator : public ast::tools::Visitor
        {

        public:

            /**
             * Constructs a GetterGenerator instance.
             */

            inline GetterGenerator( builder::Scope & scope );

        public:

            /**
             * @param astExpression AST expression
             * @return Runtime value of the expression
             *
             * Generates the IR code corresponding to the specified expression, and returns a LLVM value containing the final runtime value of the expression.
             *
             * If the expression is actually a list of expressions, only the code for the first one will be built.
             */

            inline llvm::Value * run( ast::Expression & astExpression );

        public:

            /**
             * This method should only be called by instances of ast::expr::Bool.
             */

            virtual void visit( ast::expr::Bool & astBoolExpression );

            /**
             * This method should only be called by instances of ast::expr::Binary.
             */

            virtual void visit( ast::expr::Binary & astBinaryExpression );

            /**
             * This method should only be called by instances of ast::expr::Class.
             */

            virtual void visit( ast::expr::Class & astClassExpression );

            /**
             * This method should only be called by instances of ast::expr::Dict.
             */

            virtual void visit( ast::expr::Dict & astDictExpression );

            /**
             * This method should only be called by instances of ast::expr::Function.
             */

            virtual void visit( ast::expr::Function & astFunctionExpression );

            /**
             * This method should only be called by instances of ast::expr::List.
             */

            virtual void visit( ast::expr::List & astListExpression );

            /**
             * This method should only be called by instances of ast::expr::Multary.
             */

            virtual void visit( ast::expr::Multary & astMultaryExpression );

            /**
             * This method should only be called by instances of ast::expr::Null.
             */

            virtual void visit( ast::expr::Null & astNullExpression );

            /**
             * This method should only be called by instances of ast::expr::Number.
             */

            virtual void visit( ast::expr::Number & astNumberExpression );

            /**
             * This method should only be called by instances of ast::expr::String.
             */

            virtual void visit( ast::expr::String & astStringExpression );

            /**
             * This method should only be called by instances of ast::expr::Unary.
             */

            virtual void visit( ast::expr::Unary & astUnaryExpression );

            /**
             * This method should only be called by instances of ast::expr::Undefined.
             */

            virtual void visit( ast::expr::Undefined & astUndefinedExpression );

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
#include "castel/ast/expr/Bool.hh"
#include "castel/ast/expr/Class.hh"
#include "castel/ast/expr/Dict.hh"
#include "castel/ast/expr/Function.hh"
#include "castel/ast/expr/List.hh"
#include "castel/ast/expr/Multary.hh"
#include "castel/ast/expr/Null.hh"
#include "castel/ast/expr/Number.hh"
#include "castel/ast/expr/String.hh"
#include "castel/ast/expr/Unary.hh"
#include "castel/ast/expr/Undefined.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/Expression.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        GetterGenerator::GetterGenerator( builder::Scope & scope )
            : mContext( scope.context( ) )
            , mScope( scope )
            , mLLVMValue( nullptr )
        {
        }

        llvm::Value * GetterGenerator::run( ast::Expression & astExpression )
        {
            astExpression.accept( * this );
            return mLLVMValue;
        }

    }

}
