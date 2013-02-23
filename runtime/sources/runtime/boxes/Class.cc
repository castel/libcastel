#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/boxes/Object.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Class;

bool Class::operatorBoolCast( void )
{
    return true;
}

runtime::Box * Class::operatorNew( unsigned int argc, runtime::Box ** argv )
{
    runtime::boxes::Object * instance = runtime::helper::create< runtime::boxes::Object >( this );

    for ( runtime::boxes::Class * type = this; type != nullptr; type = type->parent( ) )
        type->mInitializer( instance, mEnvironment, argc, argv );

    return instance;
}
