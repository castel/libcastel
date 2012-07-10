#include <sstream>
#include <string>

#include "p9/lexer/Exception.hh"
#include "p9/lexer/Lexer.hh"

using namespace p9;
using namespace p9::lexer;

Exception::Exception ( std::string const & message )
    : mMessage( message )
{
    std::ostringstream stringstream;
    stringstream << message;
    mWhat = stringstream.str( );
}
