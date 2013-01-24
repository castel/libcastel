#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Undefined * Castel_Undefined_create( void )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Undefined >( );
}
