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
    unsigned int newArgc = argc + mArgc;
    runtime::Box * newArgv[ newArgc ];

    std::copy( mArgv, mArgv + mArgc, newArgv );
    std::copy( argv, argv + argc, newArgv + mArgc );

    return mCallable->operatorCall( newArgc, newArgv );
}
