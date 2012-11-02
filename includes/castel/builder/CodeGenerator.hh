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
            class Bool;
            class Binary;
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

        namespace stmt
        {
            namespace decl
            {
                class Variables;
            }

            class Expression;
            class If;
            class Return;
        }

        class Expression;
        class Statement;
        class Token;

    }

    namespace builder
    {

        class Context;
        class Scope;

        class CodeGenerator : public ast::tools::Visitor
        {

        public:

            /**
             * Constructs a CodeGenerator instance.
             */

            inline CodeGenerator( builder::Context & context, builder::Scope & scope );

        public:

            /**
             * Return a LLVM value resulting from the specified AST evaluation.
             */

            inline llvm::Value * expression( ast::Expression & astExpression );

            /**
             * Generate code corresponding to the specified AST.
             */

            inline void statement( ast::Statement & astStatement );

        public:

            virtual void visit( ast::expr::Bool & astBoolExpression );
            virtual void visit( ast::expr::Binary & astBinaryExpression );
            virtual void visit( ast::expr::Class & astClassExpression );
            virtual void visit( ast::expr::Dict & astDictExpression );
            virtual void visit( ast::expr::Function & astFunctionExpression );
            virtual void visit( ast::expr::List & astListExpression );
            virtual void visit( ast::expr::Multary & astMultaryExpression );
            virtual void visit( ast::expr::Null & astNullExpression );
            virtual void visit( ast::expr::Number & astNumberExpression );
            virtual void visit( ast::expr::String & astStringExpression );
            virtual void visit( ast::expr::Unary & astUnaryExpression );
            virtual void visit( ast::expr::Undefined & astUndefinedExpression );
            virtual void visit( ast::expr::Variable & astVariableExpression );

        public:

            virtual void visit( ast::stmt::decl::Variables & astVariableDeclaration );
            virtual void visit( ast::stmt::Expression & astExpressionStatement );
            virtual void visit( ast::stmt::If & astIfStatement );
            virtual void visit( ast::stmt::Return & astReturnStatement );

        public:

            virtual void defaultAction( ast::Token & astToken );

        private:

            builder::Context & mContext;
            builder::Scope & mScope;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}

#include "castel/ast/expr/Bool.hh"
#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Class.hh"
#include "castel/ast/expr/Function.hh"
#include "castel/ast/expr/List.hh"
#include "castel/ast/expr/Multary.hh"
#include "castel/ast/expr/Null.hh"
#include "castel/ast/expr/Number.hh"
#include "castel/ast/expr/Unary.hh"
#include "castel/ast/expr/Undefined.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/If.hh"
#include "castel/ast/stmt/Return.hh"
#include "castel/ast/Statement.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        CodeGenerator::CodeGenerator( builder::Context & context, builder::Scope & scope )
            : mContext( context )
            , mScope( scope )
        {
        }

        llvm::Value * CodeGenerator::expression( ast::Expression & expression )
        {
            expression.accept( * this );

            return mValue.release( );
        }

        void CodeGenerator::statement( ast::Statement & statement )
        {
            statement.accept( * this );
        }

    }

}
