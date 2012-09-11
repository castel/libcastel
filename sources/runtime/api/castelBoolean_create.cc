#include "castel/runtime/Boolean.hh"
#include "castel/runtime/api/boolean.hh"

castel::runtime::Boolean * castelBoolean_create( castel::runtime::Boolean::InternalBoolean boolean )
{
    return castel::runtime::Boolean::create( boolean );
}
