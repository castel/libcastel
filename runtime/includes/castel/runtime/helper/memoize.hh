#pragma once

#include <functional>
#include <map>
#include <tuple>

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            template < typename Return, typename ... Parameters >
            std::function< Return ( Parameters ... ) > memoize( std::function< Return ( Parameters ... ) > fn )
            {
                std::map< std::tuple< Parameters ... >, Return > cache;

                return [=] ( Parameters ... arguments ) mutable {
                    std::tuple< Parameters ... > key( arguments ... );

                    if ( cache.find( key ) == cache.end( ) )
                        cache[ key ] = fn( arguments ... );

                    return cache[ key ];
                };
            }

        }

    }

}
