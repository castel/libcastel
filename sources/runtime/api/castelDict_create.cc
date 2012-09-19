#include "castel/runtime/Dict.hh"
#include "castel/runtime/api/dict.hh"

castel::runtime::Dict * castelDict_create( void )
{
    return castel::runtime::Dict::create( );
}
