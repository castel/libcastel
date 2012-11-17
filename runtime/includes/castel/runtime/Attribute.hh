#pragma once

namespace castel
{

    namespace runtime
    {

        class Box;

        class Context;

        /**
         */

        class Attribute
        {

            friend runtime::Context;

        protected:

            /**
             */

            virtual ~Attribute( void ) {}

        public:

            /**
             */

            virtual runtime::Box * get( runtime::Context * context, runtime::Box * instance ) const = 0;

            /**
             */

            virtual Attribute & set( runtime::Context * context, runtime::Box * instance, runtime::Box * box ) = 0;

        };

    }

}
