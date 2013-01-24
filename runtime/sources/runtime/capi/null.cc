#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Null * Castel_Null_create( void )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Null >( );
}
