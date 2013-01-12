#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Dict * castelDict_create( void )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Dict >( );
}
