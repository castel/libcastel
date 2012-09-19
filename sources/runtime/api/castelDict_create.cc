#include "castel/runtime/DictBox.hh"
#include "castel/runtime/api/dict.hh"

castel::runtime::DictBox * castelDict_create( void )
{
    return castel::runtime::DictBox::create( );
}
