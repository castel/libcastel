#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/capi/bool.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Bool * castelBool_create( castel::runtime::Context * context, bool value )
{
    return context->create< castel::runtime::boxes::Bool >( value );
}
