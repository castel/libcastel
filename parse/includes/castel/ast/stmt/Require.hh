#pragma once

#include <string>

#include "castel/ast/Statement.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        namespace stmt
        {

            class Require : public ast::Statement
            {

            public:

                inline Require( std::string const & source, std::string const & target );

            public:

                inline std::string const & source( void ) const;

                inline Require & source( std::string const & source );

            public:

                inline std::string const & target( void ) const;

                inline Require & target( std::string const & target );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::string mSource;

                std::string mTarget;

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

            void Require::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
