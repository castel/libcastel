#include <cstdlib>

#include "castel/runtime/api.hh"

void * castel_allocate( unsigned int count, unsigned int size )
{
    return std::calloc( count, size );
}
