#pragma once

#include <memory>

#include "castel/ast/expr/Multary.hh"
#include "castel/ast/Expression.hh"
#include "castel/utils/Linked.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Multary::Operand : public utils::Linked< Multary::Operand >
            {

            public:

                Operand       ( ast::Expression * expression = nullptr )
                : mExpression ( expression )
                {
                }

            public:

                ast::Expression * expression( void ) const
                {
                    return mExpression.get( );
                }

                Operand & expression( ast::Expression * expression )
                {
                    mValue.reset( expression );

                    return * this;
                }

                ast::Expression * takeExpression( void )
                {
                    return mExpression.release( );
                }

            private:

                std::unique_ptr< ast::Expression > mExpression;

            };

        }

    }

}
