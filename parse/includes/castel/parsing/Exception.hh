#pragma once

#include <exception>
#include <list>
#include <string>

#include "castel/lexing/Lexeme.hh"

namespace castel
{

    namespace parsing
    {

        class Exception : public std::exception
        {

        public:

            Exception( std::string const & message, lexing::Lexeme const & lexeme, std::list< std::string > const & expectedTokens );

            inline virtual ~Exception( void ) throw ( );

        public:

            inline std::string const & message( void ) const throw ( );

            inline lexing::Lexeme const & lexeme( void ) const throw ( );

            inline std::list< std::string > const & expectedTokens( void ) const throw ( );

        public:

            inline virtual char const * what( void ) const throw ( );

        private:

            std::string mMessage;

            lexing::Lexeme mLexeme;

            std::list< std::string > mExpectedTokens;

            std::string mWhat;

        };

    }

}

namespace castel
{

    namespace parsing
    {

        Exception::~Exception( void )
        {
        }

        std::string const & Exception::message( void ) const throw ( )
        {
            return mMessage;
        }

        lexing::Lexeme const & Exception::lexeme( void ) const throw ( )
        {
            return mLexeme;
        }

        std::list< std::string > const & Exception::expectedTokens( void ) const throw ( )
        {
            return mExpectedTokens;
        }

        char const * Exception::what( void ) const throw ( )
        {
            return mWhat.c_str( );
        }

    }

}
