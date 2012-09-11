#pragma once

#include "castel/ast/Expression.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Boolean : public ast::Expression
            {

            public:

                Boolean  ( bool value )
                : mValue ( value )
                {
                }

            public:

                bool value( void ) const
                {
                    return mValue;
                }

                Boolean & value( bool value )
                {
                    mValue = value;

                    return * this;
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( * this );
                }

            private:

                bool mValue;

            };

        }

    }

}
