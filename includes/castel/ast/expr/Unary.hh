#pragma once

#include <memory>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Unary : public ast::Expression
            {

            public:

                enum class Operator {

                    NumericPreIncrementation,
                    NumericPostIncrementation,

                    NumericPreDecrementation,
                    NumericPostDecrementation,

                    NumericPlus,
                    NumericMinus,

                    BinaryNot,

                };

            public:

                inline Unary( ast::expr::Unary::Operator type, ast::Expression * operand );

            public:

                inline ast::expr::Unary::Operator type( void ) const;

                inline Unary & type( ast::expr::Unary::Operator type );

            public:

                inline ast::Expression * operand( void ) const;

                inline Unary & operand( ast::Expression * operand );

                inline ast::Expression * takeOperand( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::expr::Unary::Operator mType;
                std::unique_ptr< ast::Expression > mOperand;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Unary::Unary( ast::expr::Unary::Operator type, ast::Expression * operand )
                : mType( type )
                , mOperand( operand )
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

            ast::Expression * Unary::operand( void ) const
            {
                return mOperand.get( );
            }

            Unary & Unary::operand( ast::Expression * operand )
            {
                mOperand.reset( operand );

                return * this;
            }

            ast::Expression * Unary::takeOperand( void )
            {
                return mOperand.release( );
            }

            void Unary::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
