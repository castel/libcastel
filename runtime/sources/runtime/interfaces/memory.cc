#include <cstdint>
#include <cstdlib>

#include "castel/runtime/interface.hh"

void * Castel_malloc( std::int32_t size, std::int32_t count )
{
    return malloc( size * count );
}
