#pragma once

#include <string>
#include <sstream>

#include "p9/lexer/Position.hh"
#include "p9/lexer/Token.hh"

namespace p9
{

    namespace lexer
    {

        class Lexeme {

        public:

            Lexeme      ( lexer::Token type, lexer::Position position = lexer::Position( ) )
            : mType     ( type     )
            , mText     (          )
            , mPosition ( position )
            {
            }

            Lexeme      ( lexer::Token type, std::string const & text, lexer::Position position )
            : mType     ( type     )
            , mText     ( text     )
            , mPosition ( position )
            {
            }

        public:

            lexer::Token type( void ) const
            {
                return mType;
            }

            lexer::Position const & position( void ) const
            {
                return mPosition;
            }

        public:

            template < typename T >
            T as( void ) const
            {
                T output;
                std::istringstream sstream( mText );
                sstream >> output;
                return output;
            }

        private:

            lexer::Token mType;

            std::string mText;

            lexer::Position mPosition;

        };

        template < >
        inline std::string Lexeme::as< std::string >( void ) const
        {
            return mText;
        }

    }

}
