#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Bool : public runtime::Box
            {

            public:

                static inline Bool * create( bool value = false );

            private:

                inline Bool( bool value );

            public:

                inline bool value( void ) const;

                inline Bool & value( bool value );

            public:

                virtual bool operatorBool( void );

            private:

                bool mValue;

            };

        }

    }

}

#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Bool * Bool::create( bool value )
            {
                void * data = ::castel_malloc( sizeof( Bool ), 1 );
                return new ( data ) Bool( value );
            }

            Bool::Bool( bool value )
                : mValue( value )
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
