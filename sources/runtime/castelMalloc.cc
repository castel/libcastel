#include <cstdlib>

#include "castel/runtime/library.hh"

extern "C"
void * castelMalloc( unsigned int size )
{
    return std::malloc( size );
}
