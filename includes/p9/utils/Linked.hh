#pragma once

#include <memory>

namespace p9
{

    namespace utils
    {

        template < typename T >
        class Linked
        {

        public:

            class Iterator;

        public:

            T * next( void ) const
            {
                return mNext.get( );
            }

            T & next( T * next )
            {
                mNext.reset( next );

                return static_cast< T& >( *this );
            }

            T * takeNext( void )
            {
                return mNext.release( );
            }

        private:

            std::unique_ptr< T > mNext;

        };

    }

}

#include "p9/utils/Linked/Iterator.hh"

namespace p9
{

    namespace utils
    {

        template < typename T >
        typename Linked< T >::Iterator begin( Linked< T > * element )
        {
            return typename Linked< T >::Iterator( static_cast< T * >( element ) );
        }

        template < typename T >
        typename Linked< T >::Iterator end( Linked< T > * element )
        {
            return typename Linked< T >::Iterator( );
        }

    }

}
