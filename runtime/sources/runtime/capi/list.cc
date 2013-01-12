#include "castel/runtime/boxes/List.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::List * castelList_create( void )
{
    return castel::runtime::helper::create< castel::runtime::boxes::List >( );
}
