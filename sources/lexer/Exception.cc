#include <sstream>
#include <string>

#include "castel/lexer/Exception.hh"
#include "castel/lexer/Lexer.hh"

using namespace castel;
using namespace castel::lexer;

Exception::Exception ( std::string const & message )
    : mMessage( message )
{
    std::ostringstream stringstream;
    stringstream << message;
    mWhat = stringstream.str( );
}
