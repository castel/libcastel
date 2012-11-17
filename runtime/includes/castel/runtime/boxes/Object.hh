#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class Class;

            class Object : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline Object( runtime::boxes::Class * type );

            };

        }

    }

}

#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/Context.hh"
#include "castel/runtime/capi.hh"

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
