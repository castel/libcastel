#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Dict * Castel_Dict_create( void )
{
    return runtime::helper::create< runtime::boxes::Dict >( );
}
