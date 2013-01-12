#pragma once

#include <string>
#include <sstream>

#include "castel/lex/MangledLexemeTypes.hh"

namespace castel
{

    namespace lex
    {

        class Lexeme
        {

        private:

            enum class AutoType : int;

        public:

            enum class Type : int;

        public:

            static char const * constTypeString( lex::Lexeme::Type type );

        public:

            inline Lexeme( lex::Lexeme::Type type, std::string const & text, std::pair< int, int > const & position );

        public:

            inline lex::Lexeme::Type type( void ) const;

        public:

            inline std::pair< int, int > const & position( void ) const;

        public:

            template < typename Type >
            inline Type as( void ) const;

        private:

            lex::Lexeme::Type mType;

            std::string mText;

            std::pair< int, int > mPosition;

        };

        enum class Lexeme::AutoType : int
        {

            #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value )
            #define CASTEL_DEMANGLE_LEXEME_TYPE( Name )
            #define CASTEL_AUTO_LEXEME_TYPE( Name ) Name,

            #include "castel/lex/types.def"

            #undef CASTEL_AUTO_LEXEME_TYPE
            #undef CASTEL_DEMANGLE_LEXEME_TYPE
            #undef CASTEL_DEFINE_LEXEME_TYPE

        };

        enum class Lexeme::Type : int
        {

            #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value ) Name = Value,
            #define CASTEL_DEMANGLE_LEXEME_TYPE( Name ) CASTEL_DEFINE_LEXEME_TYPE( Name, CASTEL_LEXING_MANGLEDLEXEMETYPES_##Name )
            #define CASTEL_AUTO_LEXEME_TYPE( Name )

            #include "castel/lex/types.def"

            #undef CASTEL_AUTO_LEXEME_TYPE
            #undef CASTEL_DEMANGLE_LEXEME_TYPE
            #undef CASTEL_DEFINE_LEXEME_TYPE

            #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value )
            #define CASTEL_DEMANGLE_LEXEME_TYPE( Name )
            #define CASTEL_AUTO_LEXEME_TYPE( Name ) Name = - ( static_cast< int >( lex::Lexeme::AutoType::Name ) + 1 ),

            #include "castel/lex/types.def"

            #undef CASTEL_AUTO_LEXEME_TYPE
            #undef CASTEL_DEMANGLE_LEXEME_TYPE
            #undef CASTEL_DEFINE_LEXEME_TYPE

        };

    }

}

namespace castel
{

    namespace lex
    {

        Lexeme::Lexeme( lex::Lexeme::Type type, std::string const & text, std::pair< int, int > const & position )
            : mType( type )
            , mText( text )
            , mPosition( position )
        {
        }

        lex::Lexeme::Type Lexeme::type( void ) const
        {
            return mType;
        }

        std::pair< int, int > const & Lexeme::position( void ) const
        {
            return mPosition;
        }

        template < typename TType >
        TType Lexeme::as( void ) const
        {
            TType output;

            std::istringstream sstream( mText );
            sstream >> output;

            return output;
        }

        template < >
        inline std::string Lexeme::as< std::string >( void ) const
        {
            return mText;
        }

    }

}
