#include "castel/runtime/NullBox.hh"
#include "castel/runtime/api/null.hh"

castel::runtime::NullBox * castelNull_create( void )
{
    return castel::runtime::NullBox::create( );
}
