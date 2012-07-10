#pragma once

#include <exception>
#include <string>

#include "p9/lexer/Lexeme.hh"

namespace p9
{

    namespace parser
    {

        class Exception : public std::exception
        {

        public:

            Exception( std::string const & message, lexer::Lexeme * lexeme );
            virtual ~Exception( void ) throw ( ) {}

        public:

            virtual std::string const & message( void ) const throw ( )
            {
                return mMessage;
            }

            virtual lexer::Lexeme * lexeme( void ) const throw ( )
            {
                return mLexeme;
            }

            virtual char const * what( void ) const throw ( )
            {
                return mWhat.c_str( );
            }

        private:

            std::string mMessage;

            lexer::Lexeme * mLexeme;

            std::string mWhat;

        };

    }

}
