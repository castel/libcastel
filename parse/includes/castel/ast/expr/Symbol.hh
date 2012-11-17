#pragma once

#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class Visitor;

        }

        namespace expr
        {

            class Symbol : public ast::Expression
            {

            public:

                class Namespace;

            public:

                inline Symbol( std::string const & name );

            public:

                inline std::string const & name( void ) const;

                inline Symbol & name( std::string const & name );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::string mName;

            };

            class Symbol::Namespace : public ast::tools::Linked< Symbol::Namespace >
            {

            public:

                inline Namespace( std::string const & name );

            public:

                inline std::string const & name( void ) const;

                inline Namespace & name( std::string const & name );

            private:

                std::string mName;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Symbol::Namespace::Namespace( std::string const & name )
                : mName( name )
            {
            }

            std::string const & Symbol::Namespace::name( void ) const
            {
                return mName;
            }

            Symbol::Namespace & Symbol::Namespace::name( std::string const & name )
            {
                mName = name;

                return * this;
            }

            Symbol::Symbol( std::string const & name )
                : mName( name )
            {
            }

            std::string const & Symbol::name( void ) const
            {
                return mName;
            }

            Symbol & Symbol::name( std::string const & name )
            {
                mName = name;

                return * this;
            }

            void Symbol::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
