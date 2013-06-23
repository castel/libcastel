#pragma once

#include <string>

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

        namespace stmt
        {

            class Require : public ast::Statement
            {

            public:

                inline Require( ast::Expression * loader, ast::Expression * parameters );

            public:

                inline ast::Expression * loader( void ) const;

                inline Require & loader( ast::Expression * loader );

                inline ast::Expression * takeLoader( void );

            public:

                inline ast::Exp

                inline Require & target( std::string const & target );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::string mSource;

                std::string mTarget;

            };

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            Require::Require( std::string const & source, std::string const & target )
                : mSource( source )
                , mTarget( target )
            {
            }

            std::string const & Require::source( void ) const
            {
                return mSource;
            }

            Require & Require::source( std::string const & source )
            {
                mSource = source;

                return * this;
            }

            std::string const & Require::target( void ) const
            {
                return mTarget;
            }

            Require & Require::target( std::string const & target )
            {
                mTarget = target;

                return * this;
            }

            void Require::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Require::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
