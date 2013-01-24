#include <algorithm>

#include "castel/runtime/boxes/Binding.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Binding;

bool Binding::operatorBoolCast( void )
{
    return true;
}

runtime::Box * Binding::operatorCall( unsigned int argc, runtime::Box ** argv )
{
    unsigned int newArgc = argc + mArgumentCount;
    runtime::Box * newArgv[ newArgc ];

    std::copy( mArguments, mArguments + mArgumentCount, newArgv );
    std::copy( argv, argv + argc, newArgv + mArgumentCount );

    return mCallable->operatorCall( newArgc, newArgv );
}
