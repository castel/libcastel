#include "castel/runtime/boxes/List.hh"
#include "castel/runtime/capi/list.hh"

castel::runtime::boxes::List * castelList_create( void )
{
    return castel::runtime::boxes::List::create( );
}
