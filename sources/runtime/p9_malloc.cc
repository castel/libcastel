#include <cstdlib>

#include "p9/runtime/library.hh"

extern "C"
void * p9_malloc( unsigned int size )
{
    return std::malloc( size );
}
