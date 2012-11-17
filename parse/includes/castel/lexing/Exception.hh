#pragma once

#include <exception>
#include <string>

namespace castel
{

    namespace lexing
    {

        class Exception : public std::exception
        {

        public:

            Exception( std::string const & message );

            virtual ~Exception( void ) throw ( ) {};

        public:

            virtual std::string const & message( void ) const throw ( );

            virtual char const * what( void ) const throw ( );

        private:

            std::string mMessage;

            std::string mWhat;

        };

    }

}
