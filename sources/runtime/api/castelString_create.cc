#include "castel/runtime/StringBox.hh"
#include "castel/runtime/api/string.hh"

castel::runtime::StringBox * castelString_create( char const * value )
{
    return castel::runtime::StringBox::create( value );
}
