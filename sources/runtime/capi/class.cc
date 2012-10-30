#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/capi/class.hh"

castel::runtime::boxes::Class * castelBool_create( castel::runtime::boxes::Class * parent )
{
    return castel::runtime::boxes::Class::create( parent );
}
