#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/capi/Undefined.hh"
#include "castel/runtime/helper/create.hh"

castel::runtime::boxes::Undefined * castelUndefined_create( void )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Undefined >( );
}
