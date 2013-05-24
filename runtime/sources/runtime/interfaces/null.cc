#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Null * Castel_Null_create( void )
{
    return runtime::helper::create< runtime::boxes::Null >( );
}
