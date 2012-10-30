#pragma once

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        class Attribute
        {

        public:

            virtual ~Attribute( void ) { };

        public:

            virtual Attribute & set( runtime::Box * box ) = 0;

            virtual runtime::Box * get( void ) const = 0;

        };

    }

}
