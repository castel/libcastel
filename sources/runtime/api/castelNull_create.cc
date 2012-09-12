#include "castel/runtime/Null.hh"
#include "castel/runtime/api/null.hh"

castel::runtime::Null * castelNull_create( void )
{
    return castel::runtime::Null::create( );
}
