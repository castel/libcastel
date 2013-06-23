#pragma once

#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        namespace expr
        {

            class External : public ast::Expression
            {

            public:

                inline External( std::string const & name );

            public:

                inline std::string const & name( void ) const;

                inline External & name( std::string const & name );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                std::string mName;

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

        namespace expr
        {

            External::External( std::string const & name )
                : mName( name )
            {
            }

            std::string const & External::name( void ) const
            {
                return mName;
            }

            External & External::name( std::string const & name )
            {
                mName = name;

                return * this;
            }

            void External::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void External::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
