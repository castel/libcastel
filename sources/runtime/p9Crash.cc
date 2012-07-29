#include <cstdlib>
#include <iostream>

#include "p9/runtime/library.hh"

extern "C"
void p9Crash( char const * message )
{
    std::cerr << message << std::endl;
    std::exit( 1 );
}
