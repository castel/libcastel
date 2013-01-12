#pragma once

namespace castel
{

    namespace runtime
    {

        class Box;

        class Module
        {

        public:

            using Signature = runtime::Box * ( runtime::Box * );

        private:

            Module( void );

        };

    }

}

#include "castel/runtime/Box.hh"
