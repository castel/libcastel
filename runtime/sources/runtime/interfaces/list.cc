#include "castel/runtime/boxes/List.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::List * Castel_List_create( void )
{
    return runtime::helper::create< runtime::boxes::List >( );
}
