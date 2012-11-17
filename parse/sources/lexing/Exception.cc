#include <sstream>
#include <string>

#include "castel/lexing/Exception.hh"

using namespace castel;
using lexing::Exception;

Exception::Exception ( std::string const & message )
    : mMessage( message )
{
    std::ostringstream stringstream;
    stringstream << message;
    mWhat = stringstream.str( );
}

std::string const & Exception::message( void ) const throw ( )
{
    return mMessage;
}

char const * Exception::what( void ) const throw ( )
{
    return mWhat.c_str( );
}
