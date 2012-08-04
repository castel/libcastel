#pragma once

#include <exception>
#include <string>

#include "castel/lexer/Lexer.hh"

namespace castel
{

    namespace lexer
    {

        class Exception : public std::exception
        {

        public:

            Exception( std::string const & message );
            virtual ~Exception( void ) throw ( ) {};

        public:

            virtual std::string const & message( void ) const throw ( )
            {
                return mMessage;
            }

            virtual char const * what( void ) const throw ( )
            {
                return mWhat.c_str( );
            }

        private:

            std::string mMessage;

            std::string mWhat;

        };

    }

}
