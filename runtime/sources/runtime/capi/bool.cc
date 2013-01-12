#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Bool * castelBool_create( bool value )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Bool >( value );
}
