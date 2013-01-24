#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Function : public runtime::Box
            {

            public:

                using Signature = runtime::Box * ( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv );

            public:

                inline Function( runtime::boxes::Function::Signature * functionPtr, unsigned int argc, runtime::Box *** environment );

            public:

                virtual bool operatorBoolCast( void );

            public:

                virtual runtime::Box * operatorCall( unsigned int argc, runtime::Box ** argv );

            private:

                runtime::boxes::Function::Signature * mFunctionPtr;

                unsigned int mArgumentCount;

                runtime::Box *** mEnvironment;

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

            Function::Function( runtime::boxes::Function::Signature functionPtr, unsigned int argumentCount, runtime::Box *** environment )
                : Box( )
                , mFunctionPtr( functionPtr )
                , mArgumentCount( argumentCount )
                , mEnvironment( environment )
            {
            }

        }

    }

}
