#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/capi/Undefined.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Undefined * castelUndefined_create( castel::runtime::Context * context )
{
    return context->create< castel::runtime::boxes::Undefined >( );
}
