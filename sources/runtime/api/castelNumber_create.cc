#include "castel/runtime/NumberBox.hh"
#include "castel/runtime/api/number.hh"

castel::runtime::NumberBox * castelNumber_create( double number )
{
    return castel::runtime::NumberBox::create( number );
}
