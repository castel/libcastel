#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Boolean : public runtime::Box
            {

            public:

                inline Boolean( bool value );

            public:

                inline bool value( void ) const;

                inline Boolean & value( bool value );

            public:

                virtual bool operatorBoolCast( void );

            private:

                bool mValue;

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

            Boolean::Boolean( bool value )
                : Box( )
                , mValue( value )
            {
            }

            bool Boolean::value( void ) const
            {
                return mValue;
            }

            Boolean & Boolean::value( bool value )
            {
                mValue = value;

                return * this;
            }

        }

    }

}
