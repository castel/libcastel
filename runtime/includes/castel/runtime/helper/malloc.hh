#pragma once

#include <cstddef>
#include <initializer_list>

#include "castel/runtime/capi.hh"

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            inline void * malloc( std::size_t size, unsigned int count = 1 )
            {
                return ::Castel_malloc( size, count );
            }

            template < typename T >
            inline T * malloc( std::size_t count = 1 )
            {
                return static_cast< T * >( runtime::helper::malloc( sizeof( T ), count ) );
            }

            template < typename T >
            inline T * malloc( std::initializer_list< T > list )
            {
                T * memory = runtime::helper::malloc< T >( list.size( ) ), * pointer = memory;

                for ( T const & t : list )
                    * pointer ++ = t;

                return memory;
            }

        }

    }

}
