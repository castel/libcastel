#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::String * Castel_String_create( std::uint8_t const * value, unsigned int length )
{
    return runtime::helper::create< runtime::boxes::String >( value, length );
}
