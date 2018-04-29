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

            class Visitor
            {

            public:

                virtual inline ~Visitor( void );

            public:

                virtual inline void visit( ast::expr::literal::Boolean & booleanLiteralAst );

                virtual inline void visit( ast::expr::literal::Class & classLiteralAst );

                virtual inline void visit( ast::expr::literal::Dict & dictLiteralAst );

                virtual inline void visit( ast::expr::literal::Function & functionLiteralAst );

                virtual inline void visit( ast::expr::literal::List & listLiteralAst );

                virtual inline void visit( ast::expr::literal::Null & nullLiteralAst );

                virtual inline void visit( ast::expr::literal::Number & numberLiteralAst );

                virtual inline void visit( ast::expr::literal::String & stringLiteralAst );

                virtual inline void visit( ast::expr::literal::Undefined & undefinedLiteralAst );

                virtual inline void visit( ast::expr::Binary & binaryExpressionAst );

                virtual inline void visit( ast::expr::Conditional & conditionalExpressionAst );

                virtual inline void visit( ast::expr::External & externalExpressionAst );

                virtual inline void visit( ast::expr::Multary & multaryExpressionAst );

                virtual inline void visit( ast::expr::Unary & unaryExpressionAst );

                virtual inline void visit( ast::expr::Variable & variableExpressionAst );

            public:

                virtual inline void visit( ast::stmt::ctrl::ForIn & forInControlAst );

                virtual inline void visit( ast::stmt::ctrl::If & ifControlAst );

                virtual inline void visit( ast::stmt::ctrl::Try & tryControlAst );

                virtual inline void visit( ast::stmt::ctrl::Until & untilControlAst );

                virtual inline void visit( ast::stmt::ctrl::While & whileControlAst );

                virtual inline void visit( ast::stmt::decl::Class & classDeclarationAst );

                virtual inline void visit( ast::stmt::decl::Function & functionDeclarationAst );

                virtual inline void visit( ast::stmt::decl::Variables & variablesDeclarationAst );

                virtual inline void visit( ast::stmt::Block & blockStatementAst );

                virtual inline void visit( ast::stmt::Expression & expressionStatementAst );

                virtual inline void visit( ast::stmt::Return & returnStatementAst );

                virtual inline void visit( ast::stmt::Throw & throwStatementAst );

            protected:

                virtual inline void defaultAction( ast::Token & tokenAst );

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

            Visitor::~Visitor( void )
            {
            }

            void Visitor::visit( ast::expr::literal::Boolean & booleanLiteralAst )
            {
                this->defaultAction( booleanLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::Class & classLiteralAst )
            {
                this->defaultAction( classLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::Dict & dictLiteralAst )
            {
                this->defaultAction( dictLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::Function & functionLiteralAst )
            {
                this->defaultAction( functionLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::List & listLiteralAst )
            {
                this->defaultAction( listLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::Null & nullLiteralAst )
            {
                this->defaultAction( nullLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::Number & numberLiteralAst )
            {
                this->defaultAction( numberLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::String & stringLiteralAst )
            {
                this->defaultAction( stringLiteralAst );
            }

            void Visitor::visit( ast::expr::literal::Undefined & undefinedLiteralAst )
            {
                this->defaultAction( undefinedLiteralAst );
            }

            void Visitor::visit( ast::expr::Binary & binaryExpressionAst )
            {
                this->defaultAction( binaryExpressionAst );
            }

            void Visitor::visit( ast::expr::Conditional & conditionalExpressionAst )
            {
                this->defaultAction( conditionalExpressionAst );
            }

            void Visitor::visit( ast::expr::External & externalExpressionAst )
            {
                this->defaultAction( externalExpressionAst );
            }

            void Visitor::visit( ast::expr::Multary & multaryExpressionAst )
            {
                this->defaultAction( multaryExpressionAst );
            }

            void Visitor::visit( ast::expr::Unary & unaryExpressionAst )
            {
                this->defaultAction( unaryExpressionAst );
            }

            void Visitor::visit( ast::expr::Variable & variableExpressionAst )
            {
                this->defaultAction( variableExpressionAst );
            }

            void Visitor::visit( ast::stmt::ctrl::ForIn & forInControlAst )
            {
                this->defaultAction( forInControlAst );
            }

            void Visitor::visit( ast::stmt::ctrl::If & ifControlAst )
            {
                this->defaultAction( ifControlAst );
            }

            void Visitor::visit( ast::stmt::ctrl::Try & tryControlAst )
            {
                this->defaultAction( tryControlAst );
            }

            void Visitor::visit( ast::stmt::ctrl::Until & untilControlAst )
            {
                this->defaultAction( untilControlAst );
            }

            void Visitor::visit( ast::stmt::ctrl::While & whileControlAst )
            {
                this->defaultAction( whileControlAst );
            }

            void Visitor::visit( ast::stmt::decl::Class & classDeclarationAst )
            {
                this->defaultAction( classDeclarationAst );
            }

            void Visitor::visit( ast::stmt::decl::Function & functionDeclarationAst )
            {
                this->defaultAction( functionDeclarationAst );
            }

            void Visitor::visit( ast::stmt::decl::Variables & variablesDeclarationAst )
            {
                this->defaultAction( variablesDeclarationAst );
            }

            void Visitor::visit( ast::stmt::Block & blockStatementAst )
            {
                this->defaultAction( blockStatementAst );
            }

            void Visitor::visit( ast::stmt::Expression & expressionStatementAst )
            {
                this->defaultAction( expressionStatementAst );
            }

            void Visitor::visit( ast::stmt::Return & returnStatementAst )
            {
                this->defaultAction( returnStatementAst );
            }

            void Visitor::visit( ast::stmt::Throw & throwStatementAst )
            {
                this->defaultAction( throwStatementAst );
            }

            void Visitor::defaultAction( ast::Token & )
            {
                throw std::runtime_error( "Unimplemented AST branch" );
            }

        }

    }

}
