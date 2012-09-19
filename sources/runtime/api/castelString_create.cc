#include "castel/runtime/String.hh"
#include "castel/runtime/api/string.hh"

castel::runtime::String * castelString_create( char const * string )
{
    return castel::runtime::String::create( string );
}
