#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

using namespace castel;
using runtime::boxes::Function;

bool Function::operatorBool( void )
{
    return true;
}

runtime::Box * Function::operatorCall( unsigned int argc, runtime::Box ** argv )
{
    if ( mArgumentCount != argc )
        ::castel_fatal( "Bad argument count" );

    return mFunctionPtr( mEnvironment, argc, argv );
}
