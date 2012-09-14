#include <sstream>

#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

void castel_unaryOperatorMissing( char const * string, runtime::Box * operand )
{
    std::ostringstream stringstream;
    stringstream << "Undefined unary " << string << " operator";
    castel_crash( stringstream.str( ).c_str( ) );
}
