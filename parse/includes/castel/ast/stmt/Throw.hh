#pragma once

#include <memory>

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

            class Throw : public ast::Statement
            {

            public:

                inline Throw( ast::tools::Hold< ast::Expression > && expression );

            public:

                inline ast::tools::Hold< ast::Expression > const & expression( void ) const;

                inline ast::tools::Hold< ast::Expression > & expression( void );

                inline Throw & expression( ast::tools::Hold< ast::Expression > && expression );

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

            Throw::Throw( ast::tools::Hold< ast::Expression > && expression )
                : mExpression( std::move( expression ) )
            {
            }

            ast::tools::Hold< ast::Expression > const & Throw::expression( void ) const
            {
                return mExpression;
            }

            ast::tools::Hold< ast::Expression > & Throw::expression( void )
            {
                return mExpression;
            }

            Throw & Throw::expression( ast::tools::Hold< ast::Expression > && expression )
            {
                mExpression = std::move( expression );

                return * this;
            }

            void Throw::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Throw::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
