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

                static inline runtime::boxes::Dict * create( void );

            private:

                inline Dict( void );

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

            runtime::boxes::Dict * Dict::create( void )
            {
                void * data = ::castel_malloc( sizeof( Dict ), 1 );
                return new ( data ) Dict( );
            }

            Dict::Dict( void )
            {
            }

        }

    }

}
