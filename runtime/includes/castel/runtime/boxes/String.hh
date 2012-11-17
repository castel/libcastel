#pragma once

#include <cstring>

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Context;

        namespace boxes
        {

            class String : public runtime::Box
            {

                friend runtime::Context;

            protected:

                inline String( char const * value, unsigned int length = 0 );

            public:

                inline char const * value( void ) const;

                inline String & value( char const * value, unsigned int length = 0 );

            public:

                inline unsigned int length( void ) const;

            public:

                virtual bool operatorBool( runtime::Context * context );

            public:

                virtual runtime::Box * operatorNumericAddition( runtime::Context * context, runtime::Box * operand );

            public:

                virtual runtime::Box * operatorComparisonEqual( runtime::Context * context, runtime::Box * operand );

                virtual runtime::Box * operatorComparisonNotEqual( runtime::Context * context, runtime::Box * operand );

            private:

                char const * mValue;

                unsigned int mLength;

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
