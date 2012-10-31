#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/boxes/Object.hh"

using namespace castel;
using runtime::boxes::Class;

bool Class::operatorBool( void )
{
    return true;
}

runtime::Box * Class::instanciate( unsigned int argc, runtime::Box ** argv )
{
    runtime::Box * instance = castel::runtime::boxes::Object::create( this );
    mInitializer( mEnvironment, instance );
    return instance;
}
