#include "castel/runtime/UndefinedBox.hh"
#include "castel/runtime/api/undefined.hh"

castel::runtime::UndefinedBox * castelUndefined_create( void )
{
    return castel::runtime::UndefinedBox::create( );
}
