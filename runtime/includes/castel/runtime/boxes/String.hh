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

                inline String( char const * value, unsigned int length = 0 );

            public:

                inline char const * value( void ) const;

                inline String & value( char const * value, unsigned int length = 0 );

            public:

                inline unsigned int length( void ) const;

            public:

                virtual bool operatorBoolCast( void );

            public:

                virtual runtime::Box * operatorAddition( runtime::Box * operand );

            public:

                virtual runtime::Box * operatorEqual( runtime::Box * operand );

                virtual runtime::Box * operatorNotEqual( runtime::Box * operand );

            private:

                char const * mValue;

                unsigned int mLength;

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

            String::String( char const * value, unsigned int length )
                : Box( )
            {
                this->value( value, length );
            }

            char const * String::value( void ) const
            {
                return mValue;
            }

            String & String::value( char const * value, unsigned int length )
            {
                if ( value == nullptr )
                    length = 0;

                if ( length == 0 && value != nullptr && value[ 0 ] != '\0' )
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
