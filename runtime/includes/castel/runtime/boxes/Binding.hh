#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class Binding : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline Binding( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments );

            public:

                virtual bool operatorBool( runtime::Context * context );

            public:

                virtual runtime::Box * operatorCall( runtime::Context * context, unsigned int argc, runtime::Box ** argv );

            private:

                runtime::Box * mCallable;

                unsigned int mArgumentCount;

                runtime::Box ** mArguments;

            };

        }

    }

}

#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Context.hh"
#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Binding::Binding( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments )
                : Box( )
                , mCallable( callable )
                , mArgumentCount( argumentCount )
                , mArguments( arguments )
            {
            }

        }

    }

}
