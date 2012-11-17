#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/boxes/Object.hh"

using namespace castel;
using runtime::boxes::Class;

bool Class::operatorBool( runtime::Context * )
{
    return true;
}

runtime::Box * Class::instanciate( runtime::Context * context, unsigned int argc, runtime::Box ** argv )
{
    runtime::boxes::Object * instance = context->create< runtime::boxes::Object >( this );
    mInitializer( context, instance, mEnvironment );
    return instance;
}
