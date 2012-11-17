#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class Function : public runtime::Box
            {

                friend runtime::Context;

            public:

                using Signature = runtime::Box * ( runtime::Context * context, runtime::Box *** environment, unsigned int argc, runtime::Box ** argv );

            protected:

                inline Function( runtime::boxes::Function::Signature * functionPtr, unsigned int argc, runtime::Box *** environment );

            public:

                virtual bool operatorBool( runtime::Context * context );

            public:

                virtual runtime::Box * operatorCall( runtime::Context * context, unsigned int argc, runtime::Box ** argv );

            private:

                runtime::boxes::Function::Signature * mFunctionPtr;
                unsigned int mArgumentCount;
                runtime::Box *** mEnvironment;

            };

        }

    }

}

#include "castel/runtime/Context.hh"
#include "castel/runtime/capi.hh"

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
