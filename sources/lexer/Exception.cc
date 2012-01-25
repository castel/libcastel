#include "p9/lexer/Exception.hh"
#include "p9/lexer/Lexer.hh"

using namespace p9;
using namespace p9::lexer;

Exception::Exception( Lexer::Position const & position, std::string const & message )
: mPosition( position )
, mMessage( message )
{
}
