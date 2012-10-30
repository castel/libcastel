#pragma once

#include "castel/runtime/Attribute.hh"

namespace castel
{

    namespace runtime
    {

        class Box;

        namespace attributes
        {

            class Member : public runtime::Attribute
            {

            public:

                virtual runtime::Box * get( runtime::Box * instance ) const;

                virtual void set( runtime::Box * instance, runtime::Box * value );

            public:

                runtime::Box * mValue;

            };

        }

    }

}
