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

            public:

                inline Dict( void );

            public:

                virtual bool operatorBoolCast( void );

            };

        }

    }

}

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
