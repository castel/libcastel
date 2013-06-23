#pragma once

#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        class Expression;

        namespace stmt
        {

            class Return : public ast::Statement
            {

            public:

                inline Return( void );

                inline Return( ast::tools::Hold< ast::Expression > && expression );

            public:

                inline ast::tools::Hold< ast::Expression > const & expression( void ) const;

                inline ast::tools::Hold< ast::Expression > & expression( void );

                inline Return & expression( ast::tools::Hold< ast::Expression > && expression );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::tools::Hold< ast::Expression > mExpression;

            };

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            Return::Return( void )
                : mExpression( )
            {
            }

            Return::Return( ast::tools::Hold< ast::Expression > && expression )
                : mExpression( std::move( expression ) )
            {
            }

            ast::tools::Hold< ast::Expression > const & Return::expression( void ) const
            {
                return mExpression;
            }

            ast::tools::Hold< ast::Expression > & Return::expression( void )
            {
                return mExpression;
            }

            Return & Return::expression( ast::tools::Hold< ast::Expression > && expression )
            {
                mExpression = std::move( expression );

                return * this;
            }

            void Return::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Return::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
