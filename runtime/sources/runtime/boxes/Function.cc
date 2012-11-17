#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

using namespace castel;
using runtime::boxes::Function;

bool Function::operatorBool( runtime::Context * )
{
    return true;
}

runtime::Box * Function::operatorCall( runtime::Context * context, unsigned int argc, runtime::Box ** argv )
{
    if ( argc < mArgumentCount )
        context->fatal( "Bad argument count" );

    return mFunctionPtr( context, mEnvironment, argc, argv );
}
