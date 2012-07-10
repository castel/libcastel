#include <sstream>
#include <string>

#include "p9/lexer/Position.hh"

using namespace p9;
using namespace p9::lexer;

Position::Position ( void )
: line             ( -1 )
, column           ( -1 )
{
}

Position::Position ( long aLine, long aColumn )
: line             ( aLine   )
, column           ( aColumn )
{
}

std::string Position::toString( void ) const
{
    std::ostringstream stringstream;

    if ( this->line != -1 && this->column != -1 ) {
        stringstream << "line " << this->line << ", column " << this->column;
    } else {
        stringstream << "unknown location";
    }

    return stringstream.str( );
}
