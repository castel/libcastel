#pragma once

#include "p9/utils/Visitor.hh"

namespace p9
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
