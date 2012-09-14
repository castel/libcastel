#include <sstream>

#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

void castel_binaryOperatorMissing( char const * string, runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    std::ostringstream stringstream;
    stringstream << "Undefined binary " << string << " operator";
    castel_crash( stringstream.str( ).c_str( ) );
}
