#pragma once

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

            namespace literal
            {

                class Null : public ast::Expression
                {

                public:

                    inline Null( void );

                public:

                    virtual inline void accept( ast::tools::Visitor & visitor );

                };

            }

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

            namespace literal
            {

                Null::Null( void )
                {
                }

                void Null::accept( ast::tools::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            }

        }

    }

}
