#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Dict : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline Dict( void );

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

            Dict::Dict( void )
                : Box( )
            {
            }

        }

    }

}
