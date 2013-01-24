#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Binding : public runtime::Box
            {

            public:

                inline Binding( runtime::Box * callable, unsigned int argumentCount, runtime::Box ** arguments );

            public:

                virtual bool operatorBoolCast( void );

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
