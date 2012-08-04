#pragma once

#include <string>
#include <sstream>

#include "castel/lexer/Position.hh"
#include "castel/lexer/MangledLexemesTypes.hh"

namespace castel
{

    namespace lexer
    {

        class Lexeme {

        public:

            enum class Type {

                #define DEFINE_LEXEME_TYPE( Name, Value ) Name = Value,
                #define DEMANGLE_LEXEME_TYPE( Name ) DEFINE_LEXEME_TYPE( Name, CASTEL_LEXER_MANGLEDLEXEMESTYPES_##Name )

                #include "castel/lexer/LexemesTypes.xdef"

                #undef DEMANGLE_LEXEME_TYPE
                #undef DEFINE_LEXEME_TYPE

            };

            static char const * constTypeString( lexer::Lexeme::Type type ) {

                #define LEXEME_TYPE_IDENTIFIER_TO_CSTRING( Name ) #Name
                #define DEMANGLE_LEXEME_TYPE( Name ) if ( type == lexer::Lexeme::Type::Name ) return LEXEME_TYPE_IDENTIFIER_TO_CSTRING( Name );
                #define DEFINE_LEXEME_TYPE( Name, Value ) DEMANGLE_LEXEME_TYPE( Name )

                #include "castel/lexer/LexemesTypes.xdef"

                #undef DEFINE_LEXEME_TYPE
                #undef DEMANGLE_LEXEME_TYPE
                #undef LEXEME_TYPE_IDENTIFIER_TO_CSTRING

                return nullptr;

            }

            static char const * constTypeString( lexer::Lexeme & lexeme ) {

                return lexer::Lexeme::constTypeString( lexeme.type( ) );

            }

        public:

            Lexeme      ( void )
            : mType     ( lexer::Lexeme::Type::Invalid )
            , mText     (                              )
            , mPosition (                              )
            {
            }

            Lexeme      ( lexer::Lexeme::Type type, lexer::Position position = lexer::Position( ) )
            : mType     ( type     )
            , mText     (          )
            , mPosition ( position )
            {
            }

            Lexeme      ( lexer::Lexeme::Type type, std::string const & text, lexer::Position position )
            : mType     ( type     )
            , mText     ( text     )
            , mPosition ( position )
            {
            }

        public:

            lexer::Lexeme::Type type( void ) const
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

            lexer::Lexeme::Type mType;

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
