#pragma once

#include <algorithm>
#include <memory>

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            /**
             */

            template < typename T >
            class Linked
            {

            public:

                class Iterator;

            public:

                /**
                 */

                Iterator begin( void );

                /**
                 */

                Iterator end( void );

            public:

                /**
                 */

                T * next( void ) const;

                /**
                 */

                T & next( T * next );

                /**
                 */

                T * takeNext( void );

            private:

                std::unique_ptr< T > mNext;

            };

            /**
             */

            template < typename T >
            class Linked< T >::Iterator : public std::iterator< std::input_iterator_tag, T >
            {

            public:

                /**
                 */

                Iterator( T * node = nullptr );

            public:

                /**
                 */

                bool operator==( Iterator const & other ) const;

                /**
                 */

                bool operator!=( Iterator const & other ) const;

            public:

                /**
                 */

                Iterator & operator++( void );

            public:

                /**
                 */

                T & operator*( void ) const;

                /**
                 */

                T * operator->( void ) const;

            private:

                T * mNode;

            };

        }

    }

}

namespace castel
{

    namespace ast
    {

        namespace tools
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

            template < typename T >
            std::size_t count( Linked< T > * t )
            {
                return std::distance( ast::tools::begin( t ), ast::tools::end( t ) );
            }

            template < typename T >
            Linked< T >::Iterator::Iterator( T * node )
                : mNode( node )
            {
            }

            template < typename T >
            bool Linked< T >::Iterator::operator==( Linked< T >::Iterator const & other ) const
            {
                return mNode == other.mNode;
            }

            template < typename T >
            bool Linked< T >::Iterator::operator!=( Linked< T >::Iterator const & other ) const
            {
                return mNode != other.mNode;
            }

            template < typename T >
            typename Linked< T >::Iterator & Linked< T >::Iterator::operator++( void )
            {
                mNode = mNode->next( );

                return * this;
            }

            template < typename T >
            T & Linked< T >::Iterator::operator*( void ) const
            {
                return * mNode;
            }

            template < typename T >
            T * Linked< T >::Iterator::operator->( void ) const
            {
                return mNode;
            }

            template < typename T >
            T * Linked< T >::next( void ) const
            {
                return mNext.get( );
            }

            template < typename T >
            T & Linked< T >::next( T * next )
            {
                mNext.reset( next );

                return static_cast< T & >( * this );
            }

            template < typename T >
            T * Linked< T >::takeNext( void )
            {
                return mNext.release( );
            }

        }

    }

}
