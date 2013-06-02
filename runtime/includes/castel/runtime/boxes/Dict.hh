#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            class Dict : public runtime::Box
            {

            public:

                inline Dict( void );

            public:

                runtime::Box * item( std::vector< runtime::Box * > const & key ) const;

                Dict & item( std::vector< runtime::Box * > const & key, runtime::Box * value );

            public:

                virtual bool operatorBoolCast( void );

            public:

                virtual runtime::Box * operatorSubscript( std::uint32_t argc, runtime::Box ** argv );

            private:

                std::map< std::vector< runtime::Box * >, runtime::Box * > mItems;

            };

        }

    }

}

#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/helper/create.hh"

namespace castel
{

    namespace runtime
    {

        namespace boxes
        {

            Dict::Dict( void )
                : Box( )
            {
            }

        }

    }

}
