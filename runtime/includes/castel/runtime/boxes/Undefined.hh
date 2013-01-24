#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Undefined : public runtime::Box
            {

            public:

                inline Undefined( void );

            public:

                virtual bool operatorBoolCast( void );

            public:

                virtual runtime::Box * operatorEqual( runtime::Box * operand );

                virtual runtime::Box * operatorNotEqual( runtime::Box * operand );

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

            Undefined::Undefined( void )
                : Box( )
            {
            }

        }

    }

}
