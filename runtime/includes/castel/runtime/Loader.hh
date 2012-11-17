#pragma once

namespace castel
{

    namespace runtime
    {

        class Box;

        class Context;

        /**
         */

        class Loader : public std::enable_shared_from_this< Loader >
        {

        public:

            /**
             */

            virtual ~Loader( void ) {}

        public:

            /**
             */

            inline std::shared_ptr< Loader > sharedPointer( void );

        public:

            /**
             */

            virtual runtime::Box * load( runtime::Context & context, std::string const & path ) = 0;

        };

    }

}

#include "castel/runtime/Box.hh"
#include "castel/runtime/Context.hh"
