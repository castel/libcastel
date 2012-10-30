#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Function : runtime::Box
            {

            public:

                using Signature = runtime::Box * ( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv );

            public:

                static inline Function * create( runtime::boxes::Function::Signature * functionPtr, unsigned int argumentCount, runtime::Box *** environment );

            public:

                inline Function( runtime::boxes::Function::Signature * functionPtr, unsigned int argc, runtime::Box *** environment );

            public:

                virtual bool operatorBool( void );

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

            Function * Function::create( runtime::boxes::Function::Signature functionPtr, unsigned int argumentCount, runtime::Box *** environment )
            {
                void * data = ::castel_malloc( sizeof( Function ), 1 );
                return new ( data ) Function( functionPtr, argumentCount, environment );
            }

            Function::Function( runtime::boxes::Function::Signature functionPtr, unsigned int argumentCount, runtime::Box *** environment )
                : mFunctionPtr( functionPtr )
                , mArgumentCount( argumentCount )
                , mEnvironment( environment )
            {
            }

        }

    }

}
