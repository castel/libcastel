#include "p9/parser/Parser.hh"
#include "p9/parser/Exception.hh"

using namespace p9;
using namespace p9::parser;

Exception::Exception( Parser::Position const & position, std::string const & message )
: mPosition( position )
, mMessage( message )
{
}
