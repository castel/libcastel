#include "castel/runtime/Undefined.hh"
#include "castel/runtime/api/undefined.hh"

castel::runtime::Undefined * castelUndefined_create( void )
{
    return castel::runtime::Undefined::create( );
}
