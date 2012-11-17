#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/capi/number.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Number * castelNumber_create( castel::runtime::Context * context, double value )
{
    return context->create< castel::runtime::boxes::Number >( value );
}
