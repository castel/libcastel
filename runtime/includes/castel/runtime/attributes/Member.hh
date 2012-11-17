#pragma once

#include "castel/runtime/Attribute.hh"

namespace castel
{

    namespace runtime
    {

        class Box;

        class Context;

        namespace attributes
        {

            /**
             */

            class Member : public runtime::Attribute
            {

                friend runtime::Context;

            protected:

                /**
                 */

                inline Member( runtime::Box * value );

            public:

                /**
                 */

                virtual runtime::Box * get( runtime::Context * context, runtime::Box * instance ) const;

                /**
                 */

                virtual Attribute & set( runtime::Context * context, runtime::Box * instance, runtime::Box * value );

            public:

                runtime::Box * mValue;

            };

        }

    }

}

#include "castel/runtime/Box.hh"
#include "castel/runtime/Context.hh"

namespace castel
{

    namespace runtime
    {

        namespace attributes
        {

            Member::Member( runtime::Box * value )
                : Attribute( )
                , mValue( value )
            {
            }

        }

    }

}
