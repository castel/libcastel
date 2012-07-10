#pragma once

namespace p9
{

    namespace ast
    {

        class Visitor;

        class Token
        {

        public:

            virtual ~Token( void ) {}

        public:

            virtual void accept( Visitor & visitor ) = 0;

        };

    }

}
