#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/capi/bool.hh"

castel::runtime::boxes::Bool * castelBool_create( bool value )
{
    return castel::runtime::boxes::Bool::create( value );
}
