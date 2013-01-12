#pragma once

#include <string>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Variable : public ast::Expression
            {

            public:

                inline Variable( std::string const & name );

            public:

                inline std::string const & name( void ) const;

                inline Variable & name( std::string const & name );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

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

            Variable::Variable( std::string const & name )
                : mName( name )
            {
            }

            std::string const & Variable::name( void ) const
            {
                return mName;
            }

            Variable & Variable::name( std::string const & name )
            {
                mName = name;

                return * this;
            }

            void Variable::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
