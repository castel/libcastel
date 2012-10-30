#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/capi/Undefined.hh"

castel::runtime::boxes::Undefined * castelUndefined_create( )
{
    return castel::runtime::boxes::Undefined::create( );
}
