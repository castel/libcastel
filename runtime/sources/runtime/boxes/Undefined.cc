#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Undefined;

bool Undefined::operatorBool( void )
{
    return false;
}

runtime::Box * Undefined::operatorLogicalEqual( runtime::Box * operand )
{
    bool isOperandUndefined = dynamic_cast< runtime::boxes::Undefined * >( operand ) != nullptr;
    return runtime::helper::create< runtime::boxes::Bool >( isOperandUndefined );
}

runtime::Box * Undefined::operatorLogicalNotEqual( runtime::Box * operand )
{
    bool isOperandNotUndefined = dynamic_cast< runtime::boxes::Undefined * >( operand ) == nullptr;
    return runtime::helper::create< runtime::boxes::Bool >( isOperandNotUndefined );
}
