#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class Bool : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline Bool( bool value );

            public:

                inline bool value( void ) const;

                inline Bool & value( bool value );

            public:

                virtual bool operatorBool( runtime::Context * context );

            private:

                bool mValue;

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

            Bool::Bool( bool value )
                : Box( )
                , mValue( value )
            {
            }

            bool Bool::value( void ) const
            {
                return mValue;
            }

            Bool & Bool::value( bool value )
            {
                mValue = value;

                return * this;
            }

        }

    }

}
