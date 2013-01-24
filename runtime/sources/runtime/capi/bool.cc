#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Boolean * Castel_Boolean_create( bool value )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Boolean >( value );
}
