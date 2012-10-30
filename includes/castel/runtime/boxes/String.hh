#pragma once

#include <cstring>

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class String : public runtime::Box
            {

            public:

                static inline String * create( char const * value = nullptr, unsigned int length = 0 );

            private:

                inline String( char const * value, unsigned int length = 0 );

            public:

                inline char const * value( void ) const;

                inline String & value( char const * value, unsigned int length = 0 );

            public:

                inline unsigned int length( void ) const;

            public:

                virtual bool operatorBool( void );

            public:

                virtual runtime::Box * operatorNumericAddition( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorComparisonEqual( runtime::Box * operand );

                virtual runtime::Box * operatorComparisonNotEqual( runtime::Box * operand );

            private:

                char const * mValue;
                unsigned int mLength;

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

            String * String::create( char const * value, unsigned int length )
            {
                void * data = ::castel_malloc( sizeof( String ), 1 );
                return new ( data ) String( value, length );
            }

            String::String( char const * value, unsigned int length )
            {
                this->value( value, length );
            }

            char const * String::value( void ) const
            {
                return mValue;
            }

            String & String::value( char const * value, unsigned int length )
            {
                if ( length == 0 && value && value[ 0 ] )
                    length = std::strlen( value );

                mValue = value;
                mLength = length;

                return * this;
            }

            unsigned int String::length( void ) const
            {
                return mLength;
            }

        }

    }

}
