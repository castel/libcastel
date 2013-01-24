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

                inline Binding( runtime::Box * callable, unsigned int argc, runtime::Box ** argv );

            public:

                virtual bool operatorBoolCast( void );

            public:

                virtual runtime::Box * operatorCall( unsigned int argc, runtime::Box ** argv );

            private:

                runtime::Box * mCallable;

                unsigned int mArgc;

                runtime::Box ** mArgv;

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

            Binding::Binding( runtime::Box * callable, unsigned int argc, runtime::Box ** argv )
                : Box( )
                , mCallable( callable )
                , mArgc( argc )
                , mArgv( argv )
            {
            }

        }

    }

}
