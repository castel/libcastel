#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Boolean * Castel_Boolean_create( bool value )
{
    return runtime::helper::create< runtime::boxes::Boolean >( value );
}
