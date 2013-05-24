#pragma once

#include <cstdlib>
#include <iostream>

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            class Fatal
            {

            public:

                [[noreturn]]
                inline ~Fatal( void )
                { std::exit( 1 ); }

            public:

                template < typename T >
                inline auto operator<<( T const & t ) -> decltype( std::cerr << t )
                { return std::cerr << t; }

            };

        }

    }

}
