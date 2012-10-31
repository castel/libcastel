#pragma once

#include "castel/runtime/Attribute.hh"

namespace castel
{

    namespace runtime
    {

        class Box;

        namespace boxes
        {

            class Function;

        }

        namespace attributes
        {

            class Method : public runtime::Attribute
            {

            public:

                inline Method( runtime::boxes::Function * function );

            public:

                virtual runtime::Box * get( runtime::Box * instance ) const;

                virtual Attribute & set( runtime::Box * instance, runtime::Box * value );

            public:

                runtime::boxes::Function * mFunction;

            };

        }

    }

}

#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace attributes
        {

            Method::Method( runtime::boxes::Function * function )
                : mFunction( function )
            {
            }

        }

    }

}
