#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/capi/string.hh"

castel::runtime::boxes::String * castelString_create( char const * value )
{
    return castel::runtime::boxes::String::create( value );
}
