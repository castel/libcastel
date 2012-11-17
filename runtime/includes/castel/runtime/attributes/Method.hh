#pragma once

#include "castel/runtime/Attribute.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Function;

        }

        class Box;

        class Context;

        /**
         */

        namespace attributes
        {

            class Method : public runtime::Attribute
            {

                friend runtime::Context;

            protected:

                /**
                 */

                inline Method( runtime::boxes::Function * function );

            public:

                /**
                 */

                virtual runtime::Box * get( runtime::Context * context, runtime::Box * instance ) const;

                /**
                 */

                virtual Attribute & set( runtime::Context * context, runtime::Box * instance, runtime::Box * value );

            public:

                runtime::boxes::Function * mFunction;

            };

        }

    }

}

#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Context.hh"

namespace castel
{

    namespace runtime
    {

        namespace attributes
        {

            Method::Method( runtime::boxes::Function * function )
                : Attribute( )
                , mFunction( function )
            {
            }

        }

    }

}
