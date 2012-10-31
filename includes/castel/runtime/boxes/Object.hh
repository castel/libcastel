#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Class;

            class Object : public runtime::Box
            {

            public:

                static inline Object * create( runtime::boxes::Class * type );

            private:

                inline Object( runtime::boxes::Class * type );

            };

        }

    }

}

#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Object * Object::create( runtime::boxes::Class * type )
            {
                void * data = ::castel_malloc( sizeof( Object ), 1 );
                return new ( data ) Object( type );
            }

            Object::Object( runtime::boxes::Class * type )
                : Box( type )
            {
            }

        }

    }

}
