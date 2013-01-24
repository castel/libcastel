#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Function;

bool Function::operatorBoolCast( void )
{
    return true;
}

runtime::Box * Function::operatorCall( unsigned int argc, runtime::Box ** argv )
{
    if ( argc < mArgumentCount )
        runtime::helper::Fatal( ) << "Bad argument count" << std::endl;

    return mFunctionPtr( mEnvironment, argc, argv );
}
