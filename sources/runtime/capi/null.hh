#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/capi/null.hh"

castel::runtime::boxes::Null * castelNull_create( void )
{
    return castel::runtime::boxes::Null::create( );
}
