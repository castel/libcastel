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

                inline Object( runtime::boxes::Class * type );

            };

        }

    }

}

#include "castel/runtime/boxes/Class.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Object::Object( runtime::boxes::Class * type )
                : Box( )
            {
                this->type( type );
            }

        }

    }

}
