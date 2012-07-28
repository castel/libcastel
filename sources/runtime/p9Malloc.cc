#include <cstdlib>

#include "p9/runtime/library.hh"

extern "C"
void * p9Malloc( unsigned int size )
{
    return std::malloc( size );
}
