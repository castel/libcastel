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

                enum class Operator {

                    New,
                    Call,
                    Subscript,

                };

            public:

                Multary     ( ast::expr::Multary::Operator type, ast::Expression * operands = nullptr )
                : mType     ( type     )
                , mOperands ( operands )
                {
                }

            public:

                ast::expr::Multary::Operator type( void ) const
                {
                    return mType;
                }

                Multary & type( ast::expr::Multary::Operator type )
                {
                    mType = type;

                    return * this;
                }

            public:

                ast::Expression * operands( void ) const
                {
                    return mOperands.get( );
                }

                Multary & operands( ast::Expression * operands )
                {
                    mOperands.reset( operands );

                    return * this;
                }

                ast::Expression * takeOperands( void )
                {
                    return mOperands.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                ast::expr::Multary::Operator mType;
                std::unique_ptr< ast::Expression > mOperands;

            };

        }

    }

}
