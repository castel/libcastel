#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/capi/number.hh"

castel::runtime::boxes::Number * castelNumber_create( double value )
{
    return castel::runtime::boxes::Number::create( value );
}
