#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/capi/null.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Null * castelNull_create( castel::runtime::Context * context )
{
    return context->create< castel::runtime::boxes::Null >( );
}
