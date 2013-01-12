#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Class * castelClass_create( castel::runtime::boxes::Class * parent, castel::runtime::boxes::Class::InitializerSignature * initializer, castel::runtime::Box *** environment )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Class >( parent, initializer, environment );
}
