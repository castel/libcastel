#pragma once

#include <utility>

#include "castel/ast/tools/List.hh"
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

            class Block : public ast::Statement
            {

            public:

                inline Block( ast::tools::List< ast::Statement > && statements );

            public:

                inline ast::tools::List< ast::Statement > const & statements( void ) const;

                inline ast::tools::List< ast::Statement > & statements( void );

                inline Block & statements( ast::tools::List< ast::Statement > && statements );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::tools::List< ast::Statement > mStatements;

            };

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"
#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            Block::Block( ast::tools::List< ast::Statement > && statements )
                : mStatements( std::move( statements ) )
            {
            }

            ast::tools::List< ast::Statement > const & Block::statements( void ) const
            {
                return mStatements;
            }

            ast::tools::List< ast::Statement > & Block::statements( void )
            {
                return mStatements;
            }

            Block & Block::statements( ast::tools::List< ast::Statement > && statements )
            {
                mStatements = std::move( statements );

                return * this;
            }

            void Block::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Block::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
