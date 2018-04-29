#pragma once

#include <cstddef>
#include <cstring>
#include <string>

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

                inline String( char const * value );

                inline String( std::uint8_t const * value, unsigned int length = 0 );

            public:

                inline std::uint8_t const * value( void ) const;

                inline String & value( std::uint8_t const * value, unsigned int length = 0 );

            public:

                inline std::string toStdString(void) const;

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

                std::uint8_t const * mValue;

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

            String::String( char const * value )
                : Box( )
            {
                this->value( reinterpret_cast< std::uint8_t const * >( value ), std::strlen( value ) );
            }

            String::String( std::uint8_t const * value, unsigned int length )
                : Box( )
            {
                this->value( value, length );
            }

            std::uint8_t const * String::value( void ) const
            {
                return mValue;
            }

            String & String::value( std::uint8_t const * value, unsigned int length )
            {
                mValue = value;
                mLength = length;

                return * this;
            }

            unsigned int String::length( void ) const
            {
                return mLength;
            }

            std::string String::toStdString( void ) const
            {
                return std::string( reinterpret_cast< char const * >( mValue ), mLength );
            }

        }

    }

}
