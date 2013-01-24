#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            template < typename Internal >
            class Resource : public runtime::Box
            {

            public:

                inline Resource( void );

                inline Resource( Internal const & value );

            public:

                inline Internal const & value( void ) const;

                inline Resource< Internal > & value( Internal const & value );

            private:

                Internal mValue;

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

            template < typename Internal >
            Resource< Internal >::Resource( void )
            {
            }

            template < typename Internal >
            Resource< Internal >::Resource( Internal const & value )
                : mValue( value )
            {
            }

            template < typename Internal >
            Internal const & Resource< Internal >::value( void ) const
            {
                return mValue;
            }

            template < typename Internal >
            Resource< Internal > & Resource< Internal >::value( Internal const & value )
            {
                mValue = value;

                return * this;
            }

        }

    }

}
