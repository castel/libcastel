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

            virtual runtime::Box * get( runtime::Box * instance ) const = 0;

            virtual Attribute & set( runtime::Box * instance, runtime::Box * box ) = 0;

        };

    }

}
