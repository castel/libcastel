#include "castel/lexing/Lexeme.hh"

using namespace castel;
using lexing::Lexeme;

char const * Lexeme::constTypeString( lexing::Lexeme::Type type )
{
    switch ( type ) {

        #define CASTEL_LEXEME_TYPE_IDENTIFIER_TO_CSTRING( Name ) #Name
        #define CASTEL_DEMANGLE_LEXEME_TYPE( Name ) case lexing::Lexeme::Type::Name: return CASTEL_LEXEME_TYPE_IDENTIFIER_TO_CSTRING( Name );
        #define CASTEL_DEFINE_LEXEME_TYPE( Name, Value ) CASTEL_DEMANGLE_LEXEME_TYPE( Name )
        #define CASTEL_AUTO_LEXEME_TYPE( Name ) CASTEL_DEMANGLE_LEXEME_TYPE( Name )

        #include "castel/lexing/types.def"

        #undef CASTEL_AUTO_LEXEME_TYPE
        #undef CASTEL_DEFINE_LEXEME_TYPE
        #undef CASTEL_DEMANGLE_LEXEME_TYPE
        #undef CASTEL_LEXEME_TYPE_IDENTIFIER_TO_CSTRING

    };

    return nullptr;
}
