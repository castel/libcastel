#pragma once

#include <memory>

#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Visitor.hh"

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

                Unary      ( ast::expr::Unary::Operator type, ast::Expression * operand )
                : mType    ( type    )
                , mOperand ( operand )
                {
                }

            public:

                ast::expr::Unary::Operator type( void ) const
                {
                    return mType;
                }

                Unary & type( ast::expr::Unary::Operator type )
                {
                    mType = type;

                    return * this;
                }

            public:

                ast::Expression * operand( void ) const
                {
                    return mOperand.get( );
                }

                Unary & operand( ast::Expression * operand )
                {
                    mOperand.reset( operand );

                    return * this;
                }

                ast::Expression * takeOperand( void )
                {
                    return mOperand.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                ast::expr::Unary::Operator mType;
                std::unique_ptr< ast::Expression > mOperand;

            };

        }

    }

}
