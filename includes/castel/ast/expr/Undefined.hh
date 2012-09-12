#pragma once

#include "castel/ast/Expression.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Undefined : public ast::Expression
            {

            public:

                Undefined ( void )
                {
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            };

        }

    }

}
