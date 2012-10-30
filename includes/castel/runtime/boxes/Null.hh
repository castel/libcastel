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

                static inline Null * create( void );

            private:

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

#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Null * Null::create( void )
            {
                void * data = ::castel_malloc( sizeof( Null ), 1 );
                return new ( data ) Null( );
            }

            Null::Null( void )
            {
            }

        }

    }

}
