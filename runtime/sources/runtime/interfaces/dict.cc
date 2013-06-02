#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Dict * Castel_Dict_create( void )
{
    return runtime::helper::create< runtime::boxes::Dict >( );
}

runtime::Box * Castel_Dict_get( runtime::boxes::Dict * dict, std::uint32_t argc, runtime::Box ** argv )
{
    std::vector< runtime::Box * > key;
    key.assign( argv, argv + argc );

    return dict->item( key );
}

void Castel_Dict_set( runtime::boxes::Dict * dict, std::uint32_t argc, runtime::Box ** argv, runtime::Box * value )
{
    std::vector< runtime::Box * > key;
    key.assign( argv, argv + argc );

    dict->item( key, value );
}
