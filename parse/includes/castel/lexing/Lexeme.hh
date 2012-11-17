#pragma once

#include <string>
#include <sstream>

#include "castel/lexing/MangledLexemeTypes.hh"

namespace castel
{

    namespace lexing
    {

        class Lexeme
        {

        private:

            enum class AutoType : int;

        public:

            enum class Type : int;

        public:

            static char const * constTypeString( lexing::Lexeme::Type type );

        public:

            inline Lexeme( lexing::Lexeme::Type type, std::string const & text, std::pair< int, int > const & position );

        public:

            inline lexing::Lexeme::Type type( void ) const;

        public:

            inline std::pair< int, int > const & position( void ) const;

        public:

            template < typename Type >
            inline Type as( void ) const;

        private:

            lexing::Lexeme::Type mType;

            std::string mText;

            std::pair< int, int > mPosition;

        };

        enum class Lexeme::AutoType : int
        {

            #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value )
            #define CASTEL_DEMANGLE_LEXEME_TYPE( Name )
            #define CASTEL_AUTO_LEXEME_TYPE( Name ) Name,

            #include "castel/lexing/types.def"

            #undef CASTEL_AUTO_LEXEME_TYPE
            #undef CASTEL_DEMANGLE_LEXEME_TYPE
            #undef CASTEL_DEFINE_LEXEME_TYPE

        };

        enum class Lexeme::Type : int
        {

            #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value ) Name = Value,
            #define CASTEL_DEMANGLE_LEXEME_TYPE( Name ) CASTEL_DEFINE_LEXEME_TYPE( Name, CASTEL_LEXING_MANGLEDLEXEMETYPES_##Name )
            #define CASTEL_AUTO_LEXEME_TYPE( Name )

            #include "castel/lexing/types.def"

            #undef CASTEL_AUTO_LEXEME_TYPE
            #undef CASTEL_DEMANGLE_LEXEME_TYPE
            #undef CASTEL_DEFINE_LEXEME_TYPE

            #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value )
            #define CASTEL_DEMANGLE_LEXEME_TYPE( Name )
            #define CASTEL_AUTO_LEXEME_TYPE( Name ) Name = - ( static_cast< int >( lexing::Lexeme::AutoType::Name ) + 1 ),

            #include "castel/lexing/types.def"

            #undef CASTEL_AUTO_LEXEME_TYPE
            #undef CASTEL_DEMANGLE_LEXEME_TYPE
            #undef CASTEL_DEFINE_LEXEME_TYPE

        };

    }

}

namespace castel
{

    namespace lexing
    {

        Lexeme::Lexeme( lexing::Lexeme::Type type, std::string const & text, std::pair< int, int > const & position )
            : mType( type )
            , mText( text )
            , mPosition( position )
        {
        }

        lexing::Lexeme::Type Lexeme::type( void ) const
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
