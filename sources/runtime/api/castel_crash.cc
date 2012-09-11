#include <cstdlib>
#include <iostream>

#include "castel/runtime/api.hh"

void castel_crash( char const * message )
{
    std::cerr << "Fatal error : " << message << std::endl;
    std::exit( 1 );
}
