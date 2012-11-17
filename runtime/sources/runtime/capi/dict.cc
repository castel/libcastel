#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/capi/dict.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Dict * castelDict_create( castel::runtime::Context * context )
{
    return context->create< castel::runtime::boxes::Dict >( );
}
