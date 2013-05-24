#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::String * Castel_String_create( char const * value )
{
    return runtime::helper::create< runtime::boxes::String >( value );
}
