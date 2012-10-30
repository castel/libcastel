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

                static inline Undefined * create( void );

            private:

                inline Undefined( void );

            public:

                virtual bool operatorBool( void );

            public:

                virtual runtime::Box * operatorLogicalEqual( runtime::Box * operand );

                virtual runtime::Box * operatorLogicalNotEqual( runtime::Box * operand );

            };

        }

    }

}

#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Undefined * Undefined::create( void )
            {
                void * data = ::castel_malloc( sizeof( Undefined ), 1 );
                return new ( data ) Undefined( );
            }

            Undefined::Undefined( void )
            {
            }

        }

    }

}
