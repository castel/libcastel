#pragma once

#include "castel/runtime/helper/malloc.hh"

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            template < typename T, typename ... Parameters >
            inline T * create( Parameters ... arguments )
            {
                return new ( runtime::helper::malloc< T >( ) ) T( arguments ... );
            }

        }

    }

}
