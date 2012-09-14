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

            class Multary : public ast::Expression
            {

            public:

                class Operand;

            public:

                Multary     ( lexer::Lexeme::Type type = lexer::Lexeme::Type::Invalid, ast::expr::Multary::Operand * operands = nullptr )
                : mType     ( type     )
                , mOperands ( operands )
                {
                }

            public:

                ast::expr::Multary::Operand * operands( void ) const
                {
                    return mOperands.get( );
                }

                Mutary & operands( ast::expr::Multary::Operand * operands )
                {
                    mOperands.reset( operands );

                    return * this;
                }

                ast::expr::Multary::Operand * takeOperands( void )
                {
                    return mOperands.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                lexer::Lexeme::Type mType;
                std::unique_ptr< ast::expr::Multary::Operand > mOperands;

            };

        }

    }

}

#include "castel/ast/expr/Mutary/Operand.hh"
