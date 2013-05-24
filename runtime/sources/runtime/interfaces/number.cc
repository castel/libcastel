#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Number * Castel_Number_create( double value )
{
    return runtime::helper::create< runtime::boxes::Number >( value );
}
