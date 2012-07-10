#pragma once

#include <string>

namespace p9
{

    namespace lexer
    {

        struct Position
        {

        public:

            Position( void );
            Position( long, long );

        public:

            std::string toString( void ) const;

        public:

            long line;
            long column;

        };

    }

}
