#include <sstream>
#include <string>

#include "castel/lexer/Lexeme.hh"
#include "castel/lexer/Position.hh"
#include "castel/parser/Exception.hh"
#include "castel/parser/Parser.hh"

using namespace castel;
using namespace castel::parser;

Exception::Exception ( std::string const & message, lexer::Lexeme * lexeme )
: mMessage           ( message )
, mLexeme            ( lexeme  )
{
    if ( lexeme ) {

        lexer::Position const & position = mLexeme->position( );

        std::ostringstream stringstream;
        stringstream << message << " " << lexer::Lexeme::constTypeString( lexeme->type( ) ) << " at " << position.toString( );
        mWhat = stringstream.str( );

    } else {

        mWhat = message;

    }

}
