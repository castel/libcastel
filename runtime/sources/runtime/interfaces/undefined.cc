#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Undefined * Castel_Undefined_create( void )
{
    return runtime::helper::create< runtime::boxes::Undefined >( );
}
