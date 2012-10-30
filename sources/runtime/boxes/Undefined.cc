#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Undefined.hh"

using namespace castel;
using runtime::boxes::Undefined;

bool Undefined::operatorBool( void )
{
    return false;
}

runtime::Box * Undefined::operatorLogicalEqual( runtime::Box * operand )
{
    return runtime::boxes::Bool::create( dynamic_cast< runtime::boxes::Undefined * >( operand ) != nullptr );
}

runtime::Box * Undefined::operatorLogicalNotEqual( runtime::Box * operand )
{
    return runtime::boxes::Bool::create( dynamic_cast< runtime::boxes::Undefined * >( operand ) == nullptr );
}
