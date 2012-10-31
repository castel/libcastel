#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Box;

        namespace boxes
        {

            class Binding : public runtime::Box
            {

            public:

                static inline Binding * create( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments );

            protected:

                inline Binding( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments );

            public:

                virtual runtime::Box * operatorCall( unsigned int argc, runtime::Box ** argv );

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
#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Binding * Binding::create( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments )
            {
                void * data = ::castel_malloc( sizeof( Binding ), 1 );
                return new ( data ) Binding( callable, argumentCount, arguments );
            }

            Binding::Binding( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments )
                : mCallable( callable )
                , mArgumentCount( argumentCount )
                , mArguments( arguments )
            {
            }

        }

    }

}
