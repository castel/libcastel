#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Number * castelNumber_create( double value )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Number >( value );
}
