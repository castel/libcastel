#pragma once

#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        class Token
        {

        public:

            virtual ~Token( void ) {}

        public:

            virtual void accept( utils::Visitor & visitor ) = 0;

        };

    }

}
