#pragma once

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

        class Token;

        namespace tools
        {

            class Visitor
            {

            public:

                virtual inline ~Visitor( void );

            public:

                virtual inline void visit( ast::expr::Bool & astBoolExpression );
                virtual inline void visit( ast::expr::Binary & astBinaryExpression );
                virtual inline void visit( ast::expr::Class & astClassExpression );
                virtual inline void visit( ast::expr::Dict & astDictExpression );
                virtual inline void visit( ast::expr::Function & astFunctionExpression );
                virtual inline void visit( ast::expr::List & astListExpression );
                virtual inline void visit( ast::expr::Multary & astMultaryExpression );
                virtual inline void visit( ast::expr::Null & astNullExpression );
                virtual inline void visit( ast::expr::Number & astNumberExpression );
                virtual inline void visit( ast::expr::String & astStringExpression );
                virtual inline void visit( ast::expr::Unary & astUnaryExpression );
                virtual inline void visit( ast::expr::Undefined & astUndefinedExpression );
                virtual inline void visit( ast::expr::Variable & astVariableExpression );

            public:

                virtual inline void visit( ast::stmt::decl::Variables & astVariablesDeclaration );
                virtual inline void visit( ast::stmt::Expression & astExpressionStatement );
                virtual inline void visit( ast::stmt::If & astIfStatement );
                virtual inline void visit( ast::stmt::Return & astReturnStatement );

            protected:

                virtual inline void defaultAction( ast::Token & astToken );

            };

        }

    }

}

#include <stdexcept>

#include "castel/ast/expr/Bool.hh"
#include "castel/ast/expr/Binary.hh"
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
#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/If.hh"
#include "castel/ast/stmt/Return.hh"
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

            void Visitor::visit( ast::expr::Bool & astBoolExpression )
            {
                this->defaultAction( astBoolExpression );
            }

            void Visitor::visit( ast::expr::Binary & astBinaryExpression )
            {
                this->defaultAction( astBinaryExpression );
            }

            void Visitor::visit( ast::expr::Class & astClassExpression )
            {
                this->defaultAction( astClassExpression );
            }

            void Visitor::visit( ast::expr::Dict & astDictExpression )
            {
                this->defaultAction( astDictExpression );
            }

            void Visitor::visit( ast::expr::Function & astFunctionExpression )
            {
                this->defaultAction( astFunctionExpression );
            }

            void Visitor::visit( ast::expr::List & astListExpression )
            {
                this->defaultAction( astListExpression );
            }

            void Visitor::visit( ast::expr::Multary & astMultaryExpression )
            {
                this->defaultAction( astMultaryExpression );
            }

            void Visitor::visit( ast::expr::Null & astNullExpression )
            {
                this->defaultAction( astNullExpression );
            }

            void Visitor::visit( ast::expr::Number & astNumberExpression )
            {
                this->defaultAction( astNumberExpression );
            }

            void Visitor::visit( ast::expr::String & astStringExpression )
            {
                this->defaultAction( astStringExpression );
            }

            void Visitor::visit( ast::expr::Unary & astUnaryExpression )
            {
                this->defaultAction( astUnaryExpression );
            }

            void Visitor::visit( ast::expr::Undefined & astUndefinedExpression )
            {
                this->defaultAction( astUndefinedExpression );
            }

            void Visitor::visit( ast::expr::Variable & astVariableExpression )
            {
                this->defaultAction( astVariableExpression );
            }

            void Visitor::visit( ast::stmt::decl::Variables & astVariablesDeclaration )
            {
                this->defaultAction( astVariablesDeclaration );
            }

            void Visitor::visit( ast::stmt::Expression & astExpressionStatement )
            {
                this->defaultAction( astExpressionStatement );
            }

            void Visitor::visit( ast::stmt::If & astIfStatement )
            {
                this->defaultAction( astIfStatement );
            }

            void Visitor::visit( ast::stmt::Return & astReturnStatement )
            {
                this->defaultAction( astReturnStatement );
            }

            void Visitor::defaultAction( ast::Token & )
            {
                throw std::runtime_error( "Unimplemented AST branch" );
            }

        }

    }

}
