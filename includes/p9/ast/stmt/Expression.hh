#pragma once

#include <memory>

#include "p9/ast/Expression.hh"
#include "p9/ast/Statement.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace ast
    {

        namespace stmt
        {

            class Expression : public ast::Statement
            {

            public:

                Expression( ast::Expression * expression = nullptr )
                : mExpression( expression )
                {
                }

            public:

                ast::Expression * expression( void ) const
                {
                    return mExpression.get( );
                }

                Expression & expression( ast::Expression * expression )
                {
                    mExpression.reset( expression );

                    return *this;
                }

                ast::Expression * takeExpression( void )
                {
                    return mExpression.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                std::unique_ptr< ast::Expression > mExpression;

            };

        }

    }

}
