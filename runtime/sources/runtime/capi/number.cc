#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Number * Castel_Number_create( double value )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Number >( value );
}
