#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/api/boolean.hh"

castel::runtime::BooleanBox * castelBoolean_create( bool boolean )
{
    return castel::runtime::BooleanBox::create( boolean );
}
