#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Class : public runtime::Box
            {

            public:

                using InitializerSignature = void ( runtime::Box * instance, runtime::Box *** environment );

            public:

                inline Class( runtime::boxes::Class * parent, runtime::boxes::Class::InitializerSignature * initializer, runtime::Box *** environment );

            public:

                inline runtime::boxes::Class * parent( void ) const;

                inline Class & parent( runtime::boxes::Class * parent );

            public:

                inline bool is( runtime::boxes::Class * schema );

            public:

                runtime::Box * instanciate( unsigned int argc, runtime::Box ** argv );

            public:

                virtual bool operatorBool( void );

            private:

                runtime::boxes::Class * mParent;

                runtime::boxes::Class::InitializerSignature * mInitializer;

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

            Class::Class( runtime::boxes::Class * parent, runtime::boxes::Class::InitializerSignature * initializer, runtime::Box *** environment )
                : Box( )
                , mParent( parent )
                , mInitializer( initializer )
                , mEnvironment( environment )
            {
            }

            runtime::boxes::Class * Class::parent( void ) const
            {
                return mParent;
            }

            Class & Class::parent( runtime::boxes::Class * parent )
            {
                mParent = parent;

                return * this;
            }

            bool Class::is( runtime::boxes::Class * type )
            {
                return ( type == this ) || ( mParent && mParent->is( type ) );
            }

        }

    }

}
