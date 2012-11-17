#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class List : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline List( void );

            public:

                virtual bool operatorBool( runtime::Context * context );

            };

        }

    }

}

#include "castel/runtime/Context.hh"
#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            List::List( void )
                : Box( )
            {
            }

        }

    }

}
