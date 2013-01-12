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

                inline Member( runtime::Box * value );

            public:

                virtual runtime::Box * get( runtime::Box * instance ) const;

                virtual Attribute & set( runtime::Box * instance, runtime::Box * value );

            public:

                runtime::Box * mValue;

            };

        }

    }

}

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace attributes
        {

            Member::Member( runtime::Box * value )
                : Attribute( )
                , mValue( value )
            {
            }

        }

    }

}
