#include "p9/lexer/Lexeme.hh"
#include "p9/parser/Exception.hh"
#include "p9/parser/Parser.hh"

using namespace p9;
using namespace p9::parser;

Exception::Exception( Parser::Position const & position, std::string const & message, lexer::Lexeme * lexeme )
: mPosition( position )
, mMessage( message )
, mLexeme( lexeme )
{
}
