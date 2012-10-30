#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/capi/dict.hh"

castel::runtime::boxes::Dict * castelDict_create( void )
{
    return castel::runtime::boxes::Dict::create( );
}
