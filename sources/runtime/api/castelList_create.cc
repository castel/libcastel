#include "castel/runtime/List.hh"
#include "castel/runtime/api/list.hh"

castel::runtime::List * castelList_create( void )
{
    return castel::runtime::List::create( );
}
