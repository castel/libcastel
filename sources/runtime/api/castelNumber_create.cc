#include "castel/runtime/Number.hh"
#include "castel/runtime/api/number.hh"

castel::runtime::Number * castelNumber_create( castel::runtime::Number::InternalNumber number )
{
    return castel::runtime::Number::create( number );
}
