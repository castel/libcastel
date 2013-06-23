#pragma once

#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        namespace expr
        {

            class Unary : public ast::Expression
            {

            public:

                enum class Operator {

                    PreIncrementation,
                    PostIncrementation,

                    PreDecrementation,
                    PostDecrementation,

                    Positive,
                    Negative,

                    BitwiseNot,

                    Not,

                };

            public:

                inline Unary( ast::expr::Unary::Operator type, ast::tools::Hold< ast::Expression > && operand );

            public:

                inline ast::expr::Unary::Operator type( void ) const;

                inline Unary & type( ast::expr::Unary::Operator type );

            public:

                inline ast::tools::Hold< ast::Expression > const & operand( void ) const;

                inline ast::tools::Hold< ast::Expression > & operand( void );

                inline Unary & operand( ast::tools::Hold< ast::Expression > && operand );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::expr::Unary::Operator mType;

                ast::tools::Hold< ast::Expression > mOperand;

            };

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Unary::Unary( ast::expr::Unary::Operator type, ast::tools::Hold< ast::Expression > && operand )
                : mType( type )
                , mOperand( std::move( operand ) )
            {
            }

            ast::expr::Unary::Operator Unary::type( void ) const
            {
                return mType;
            }

            Unary & Unary::type( ast::expr::Unary::Operator type )
            {
                mType = type;

                return * this;
            }

            ast::tools::Hold< ast::Expression > const & Unary::operand( void ) const
            {
                return mOperand;
            }

            ast::tools::Hold< ast::Expression > & Unary::operand( void )
            {
                return mOperand;
            }

            Unary & Unary::operand( ast::tools::Hold< ast::Expression > && operand )
            {
                mOperand = std::move( operand );

                return * this;
            }

            void Unary::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Unary::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
