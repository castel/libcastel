#include "castel/runtime/ListBox.hh"
#include "castel/runtime/api/list.hh"

castel::runtime::ListBox * castelList_create( void )
{
    return castel::runtime::ListBox::create( );
}
