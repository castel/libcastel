#include "castel/runtime/boxes/List.hh"
#include "castel/runtime/capi/list.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::List * castelList_create( castel::runtime::Context * context )
{
    return context->create< castel::runtime::boxes::List >( );
}
