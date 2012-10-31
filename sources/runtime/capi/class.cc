#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/capi/class.hh"

castel::runtime::boxes::Class * castelClass_create( castel::runtime::boxes::Class * parent, castel::runtime::boxes::Class::InitializerSignature * initializer, castel::runtime::Box *** environment )
{
    return castel::runtime::boxes::Class::create( parent, initializer, environment );
}
