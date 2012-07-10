#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Position.hh"
#include "p9/parser/Exception.hh"
#include "p9/parser/Parser.hh"

using namespace p9;
using namespace p9::parser;

Exception::Exception ( std::string const & message, lexer::Lexeme * lexeme )
: mMessage           ( message )
, mLexeme            ( lexeme )
{
    lexer::Position const & position = mLexeme->position( );

    std::ostringstream stringstream;
    stringstream << message << " at " << position.toString( );
    mWhat = stringstream.str( );
}
