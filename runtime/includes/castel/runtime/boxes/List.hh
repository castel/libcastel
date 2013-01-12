#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class List : public runtime::Box
            {

            public:

                inline List( void );

            public:

                virtual bool operatorBool( void );

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

            List::List( void )
                : Box( )
            {
            }

        }

    }

}
