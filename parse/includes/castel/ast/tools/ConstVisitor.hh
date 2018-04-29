#pragma once

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                class Boolean;

                class Class;

                class Dict;

                class Function;

                class List;

                class Null;

                class Number;

                class String;

                class Undefined;

            }

            class Binary;

            class Conditional;

            class External;

            class Multary;

            class Require;

            class Unary;

            class Variable;

        }

        namespace stmt
        {

            namespace ctrl
            {

                class ForIn;

                class If;

                class Try;

                class Until;

                class While;

            }

            namespace decl
            {

                class Class;

                class Function;

                class Variables;

            }

            class Block;

            class Expression;

            class Return;

            class Throw;

        }

        class Token;

        namespace tools
        {

            class ConstVisitor
            {

            public:

                virtual inline ~ConstVisitor( void );

            public:

                virtual inline void visit( ast::expr::literal::Boolean const & booleanLiteralAst );

                virtual inline void visit( ast::expr::literal::Class const & classLiteralAst );

                virtual inline void visit( ast::expr::literal::Dict const & dictLiteralAst );

                virtual inline void visit( ast::expr::literal::Function const & functionLiteralAst );

                virtual inline void visit( ast::expr::literal::List const & listLiteralAst );

                virtual inline void visit( ast::expr::literal::Null const & nullLiteralAst );

                virtual inline void visit( ast::expr::literal::Number const & numberLiteralAst );

                virtual inline void visit( ast::expr::literal::String const & stringLiteralAst );

                virtual inline void visit( ast::expr::literal::Undefined const & undefinedLiteralAst );

                virtual inline void visit( ast::expr::Binary const & binaryExpressionAst );

                virtual inline void visit( ast::expr::Conditional const & conditionalExpressionAst );

                virtual inline void visit( ast::expr::External const & externalExpressionAst );

                virtual inline void visit( ast::expr::Multary const & multaryExpressionAst );

                virtual inline void visit( ast::expr::Unary const & unaryExpressionAst );

                virtual inline void visit( ast::expr::Variable const & variableExpressionAst );

            public:

                virtual inline void visit( ast::stmt::ctrl::ForIn const & forInControlAst );

                virtual inline void visit( ast::stmt::ctrl::If const & ifControlAst );

                virtual inline void visit( ast::stmt::ctrl::Try const & tryControlAst );

                virtual inline void visit( ast::stmt::ctrl::Until const & untilControlAst );

                virtual inline void visit( ast::stmt::ctrl::While const & whileControlAst );

                virtual inline void visit( ast::stmt::decl::Class const & classDeclarationAst );

                virtual inline void visit( ast::stmt::decl::Function const & functionDeclarationAst );

                virtual inline void visit( ast::stmt::decl::Variables const & variablesDeclarationAst );

                virtual inline void visit( ast::stmt::Block const & blockStatementAst );

                virtual inline void visit( ast::stmt::Expression const & expressionStatementAst );

                virtual inline void visit( ast::stmt::Return const & returnStatementAst );

                virtual inline void visit( ast::stmt::Throw const & throwStatementAst );

            protected:

                virtual inline void defaultAction( ast::Token const & tokenAst );

            };

        }

    }

}

#include <stdexcept>

#include "castel/ast/expr/literal/Boolean.hh"
#include "castel/ast/expr/literal/Class.hh"
#include "castel/ast/expr/literal/Dict.hh"
#include "castel/ast/expr/literal/Function.hh"
#include "castel/ast/expr/literal/List.hh"
#include "castel/ast/expr/literal/Null.hh"
#include "castel/ast/expr/literal/Number.hh"
#include "castel/ast/expr/literal/String.hh"
#include "castel/ast/expr/literal/Undefined.hh"
#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Conditional.hh"
#include "castel/ast/expr/External.hh"
#include "castel/ast/expr/Multary.hh"
#include "castel/ast/expr/Unary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/stmt/ctrl/ForIn.hh"
#include "castel/ast/stmt/ctrl/If.hh"
#include "castel/ast/stmt/ctrl/Try.hh"
#include "castel/ast/stmt/ctrl/Until.hh"
#include "castel/ast/stmt/ctrl/While.hh"
#include "castel/ast/stmt/decl/Class.hh"
#include "castel/ast/stmt/decl/Function.hh"
#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Block.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/Return.hh"
#include "castel/ast/stmt/Throw.hh"
#include "castel/ast/Token.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            ConstVisitor::~ConstVisitor( void )
            {
            }

            void ConstVisitor::visit( ast::expr::literal::Boolean const & booleanLiteralAst )
            {
                this->defaultAction( booleanLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::Class const & classLiteralAst )
            {
                this->defaultAction( classLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::Dict const & dictLiteralAst )
            {
                this->defaultAction( dictLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::Function const & functionLiteralAst )
            {
                this->defaultAction( functionLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::List const & listLiteralAst )
            {
                this->defaultAction( listLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::Null const & nullLiteralAst )
            {
                this->defaultAction( nullLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::Number const & numberLiteralAst )
            {
                this->defaultAction( numberLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::String const & stringLiteralAst )
            {
                this->defaultAction( stringLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::literal::Undefined const & undefinedLiteralAst )
            {
                this->defaultAction( undefinedLiteralAst );
            }

            void ConstVisitor::visit( ast::expr::Binary const & binaryExpressionAst )
            {
                this->defaultAction( binaryExpressionAst );
            }

            void ConstVisitor::visit( ast::expr::Conditional const & conditionalExpressionAst )
            {
                this->defaultAction( conditionalExpressionAst );
            }

            void ConstVisitor::visit( ast::expr::External const & externalExpressionAst )
            {
                this->defaultAction( externalExpressionAst );
            }

            void ConstVisitor::visit( ast::expr::Multary const & multaryExpressionAst )
            {
                this->defaultAction( multaryExpressionAst );
            }

            void ConstVisitor::visit( ast::expr::Unary const & unaryExpressionAst )
            {
                this->defaultAction( unaryExpressionAst );
            }

            void ConstVisitor::visit( ast::expr::Variable const & variableExpressionAst )
            {
                this->defaultAction( variableExpressionAst );
            }

            void ConstVisitor::visit( ast::stmt::ctrl::ForIn const & forInControlAst )
            {
                this->defaultAction( forInControlAst );
            }

            void ConstVisitor::visit( ast::stmt::ctrl::If const & ifControlAst )
            {
                this->defaultAction( ifControlAst );
            }

            void ConstVisitor::visit( ast::stmt::ctrl::Try const & tryControlAst )
            {
                this->defaultAction( tryControlAst );
            }

            void ConstVisitor::visit( ast::stmt::ctrl::Until const & untilControlAst )
            {
                this->defaultAction( untilControlAst );
            }

            void ConstVisitor::visit( ast::stmt::ctrl::While const & whileControlAst )
            {
                this->defaultAction( whileControlAst );
            }

            void ConstVisitor::visit( ast::stmt::decl::Class const & classDeclarationAst )
            {
                this->defaultAction( classDeclarationAst );
            }

            void ConstVisitor::visit( ast::stmt::decl::Function const & functionDeclarationAst )
            {
                this->defaultAction( functionDeclarationAst );
            }

            void ConstVisitor::visit( ast::stmt::decl::Variables const & variablesDeclarationAst )
            {
                this->defaultAction( variablesDeclarationAst );
            }

            void ConstVisitor::visit( ast::stmt::Block const & blockStatementAst )
            {
                this->defaultAction( blockStatementAst );
            }

            void ConstVisitor::visit( ast::stmt::Expression const & expressionStatementAst )
            {
                this->defaultAction( expressionStatementAst );
            }

            void ConstVisitor::visit( ast::stmt::Return const & returnStatementAst )
            {
                this->defaultAction( returnStatementAst );
            }

            void ConstVisitor::visit( ast::stmt::Throw const & throwStatementAst )
            {
                this->defaultAction( throwStatementAst );
            }

            void ConstVisitor::defaultAction( ast::Token const & )
            {
                throw std::runtime_error( "Unimplemented AST branch" );
            }

        }

    }

}
