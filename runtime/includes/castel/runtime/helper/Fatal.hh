#pragma once

#include <exception>
#include <sstream>

#include "castel/runtime/capi.hh"

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
                { castel_fatal( mStream.str( ).c_str( ) ); throw std::exception( ); }

            private:

                std::ostringstream mStream;

            public:

                template < typename T >
                inline auto operator<<( T const & t ) -> decltype( mStream << t )
                { return mStream << t; }
            };

        }

    }

}
