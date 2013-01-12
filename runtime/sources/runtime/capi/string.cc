#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::String * castelString_create( char const * value )
{
    return castel::runtime::helper::create< castel::runtime::boxes::String >( value );
}
