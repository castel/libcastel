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

            class Expression : public ast::Statement
            {

            public:

                inline Expression( ast::Expression * expression = nullptr );

            public:

                inline ast::Expression * expression( void ) const;

                inline Expression & expression( ast::Expression * expression );

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

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            Expression::Expression( ast::Expression * expression )
                : mExpression( expression )
            {
            }

            ast::Expression * Expression::expression( void ) const
            {
                return mExpression.get( );
            }

            Expression & Expression::expression( ast::Expression * expression )
            {
                mExpression.reset( expression );

                return * this;
            }

            ast::Expression * Expression::takeExpression( void )
            {
                return mExpression.release( );
            }

            void Expression::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
