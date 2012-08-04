#include <cstdlib>
#include <iostream>

#include "castel/runtime/library.hh"

extern "C"
void castelCrash( char const * message )
{
    std::cerr << "Fatal error";

    if ( message )
        std::cerr << " : " << message;

    std::cerr << std::endl;

    std::exit( 1 );
}
