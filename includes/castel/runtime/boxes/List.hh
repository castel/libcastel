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

                static inline runtime::boxes::List * create( void );

            private:

                inline List( void );

            public:

                virtual bool operatorBool( void );

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

            runtime::boxes::List * List::create( void )
            {
                void * data = ::castel_malloc( sizeof( List ), 1 );
                return new ( data ) List( );
            }

            List::List( void )
            {
            }

        }

    }

}
