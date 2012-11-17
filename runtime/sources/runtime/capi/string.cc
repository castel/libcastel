#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/capi/string.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::String * castelString_create( castel::runtime::Context * context, char const * value )
{
    return context->create< castel::runtime::boxes::String >( value );
}
