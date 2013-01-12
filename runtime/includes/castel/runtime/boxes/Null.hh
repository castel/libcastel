#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Null : public runtime::Box
            {

            public:

                inline Null( void );

            public:

                virtual bool operatorBool( void );

            public:

                virtual runtime::Box * operatorLogicalEqual( runtime::Box * operand );

                virtual runtime::Box * operatorLogicalNotEqual( runtime::Box * operand );

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

            Null::Null( void )
                : Box( )
            {
            }

        }

    }

}
