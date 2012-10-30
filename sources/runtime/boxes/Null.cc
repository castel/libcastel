#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Null.hh"

using namespace castel;
using runtime::boxes::Null;

bool Null::operatorBool( void )
{
    return false;
}

runtime::Box * Null::operatorLogicalEqual( runtime::Box * operand )
{
    return runtime::boxes::Bool::create( dynamic_cast< runtime::boxes::Null * >( operand ) != nullptr );
}

runtime::Box * Null::operatorLogicalNotEqual( runtime::Box * operand )
{
    return runtime::boxes::Bool::create( dynamic_cast< runtime::boxes::Null * >( operand ) == nullptr );
}
