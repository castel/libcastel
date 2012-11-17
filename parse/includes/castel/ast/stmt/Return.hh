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

            class Return : public ast::Statement
            {

            public:

                inline Return( ast::Expression * expression = nullptr );

            public:

                inline ast::Expression * expression( void ) const;

                inline Return & expression( ast::Expression * expression );

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

            Return::Return( ast::Expression * expression )
                : mExpression( expression )
            {
            }

            ast::Expression * Return::expression( void ) const
            {
                return mExpression.get( );
            }

            Return & Return::expression( ast::Expression * expression )
            {
                mExpression.reset( expression );

                return * this;
            }

            ast::Expression * Return::takeExpression( void )
            {
                return mExpression.release( );
            }

            void Return::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
