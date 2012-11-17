#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/capi/class.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Class * castelClass_create( castel::runtime::Context * context, castel::runtime::boxes::Class * parent, castel::runtime::boxes::Class::InitializerSignature * initializer, castel::runtime::Box *** environment )
{
    return context->create< castel::runtime::boxes::Class >( parent, initializer, environment );
}
