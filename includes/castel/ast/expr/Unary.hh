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

                Unary      ( lexer::Lexeme::Type type = lexer::Lexeme::Type::Invalid, ast::Expression * operand )
                : mType    ( type    )
                , mOperand ( operand )
                {
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

                lexer::Lexeme::Type mType;
                std::unique_ptr< ast::Expression > mOperand;

            };

        }

    }

}
