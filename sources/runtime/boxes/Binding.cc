#include <algorithm>

#include "castel/runtime/boxes/Binding.hh"
#include "castel/runtime/capi.hh"

using namespace castel;
using runtime::boxes::Binding;

runtime::Box * Binding::operatorCall( unsigned int argc, runtime::Box ** argv )
{
    unsigned int newArgc = argc + mArgumentCount;
    runtime::Box ** newArgv = reinterpret_cast< runtime::Box ** >( ::castel_malloc( sizeof( runtime::Box * ), newArgc ) );

    std::copy( mArguments, mArguments + mArgumentCount, newArgv );
    std::copy( argv, argv + argc, newArgv + mArgumentCount );

    return mCallable->operatorCall( newArgc, newArgv );
}
