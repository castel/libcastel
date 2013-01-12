#pragma once

namespace castel
{

    namespace runtime
    {

        class Box;

        class Module
        {

        public:

            using Signature = runtime::Box * ( void * runner );

            using GlobalInitializerSignature = runtime::Box * ( void * runner, char const * globalName );

        private:

            Module( void );

        };

    }

}

#include "castel/runtime/Box.hh"
