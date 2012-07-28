#pragma once

namespace p9
{

    namespace utils
    {

        template < typename T >
        class Linked< T >::Iterator
        {

        public:

            Iterator ( void )
            : mNode  ( nullptr )
            {
            }

            Iterator ( T * node )
            : mNode  ( node )
            {
            }

        public:

            bool operator==( Iterator const & other ) const
            {
                return mNode == other.mNode;
            }

            bool operator!=( Iterator const & other ) const
            {
                return mNode != other.mNode;
            }

        public:

            Iterator & operator++( void )
            {
                mNode = mNode->next( );

                return *this;
            }

        public:

            T & operator*( void )
            {
                return *mNode;
            }

            T * operator->( void )
            {
                return mNode;
            }

        private:

            T * mNode;

        };

    }

}
