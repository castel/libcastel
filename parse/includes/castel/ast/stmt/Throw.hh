#pragma once

#include <memory>

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        class Expression;

        namespace stmt
        {

            class Throw : public ast::Statement
            {

            public:

                inline Throw( ast::Expression * expression );

            public:

                inline ast::Expression * expression( void ) const;

                inline Throw & expression( ast::Expression * expression );

                inline ast::Expression * takeExpression( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::unique_ptr< ast::Expression > mExpression;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            Throw::Throw( ast::Expression * expression )
                : mExpression( expression )
            {
            }

            ast::Expression * Throw::expression( void ) const
            {
                return mExpression.get( );
            }

            Throw & Throw::expression( ast::Expression * expression )
            {
                mExpression.reset( expression );

                return * this;
            }

            ast::Expression * Throw::takeExpression( void )
            {
                return mExpression.release( );
            }

            void Throw::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
