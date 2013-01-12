#pragma once

#include <exception>
#include <list>
#include <string>

#include "castel/lex/Lexeme.hh"

namespace castel
{

    namespace parse
    {

        class Exception : public std::exception
        {

        public:

            Exception( std::string const & message, lex::Lexeme const & lexeme, std::list< std::string > const & expectedTokens );

            inline virtual ~Exception( void ) throw ( );

        public:

            inline std::string const & message( void ) const throw ( );

            inline lex::Lexeme const & lexeme( void ) const throw ( );

            inline std::list< std::string > const & expectedTokens( void ) const throw ( );

        public:

            inline virtual char const * what( void ) const throw ( );

        private:

            std::string mMessage;

            lex::Lexeme mLexeme;

            std::list< std::string > mExpectedTokens;

            std::string mWhat;

        };

    }

}

namespace castel
{

    namespace parse
    {

        Exception::~Exception( void ) throw ( )
        {
        }

        std::string const & Exception::message( void ) const throw ( )
        {
            return mMessage;
        }

        lex::Lexeme const & Exception::lexeme( void ) const throw ( )
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
