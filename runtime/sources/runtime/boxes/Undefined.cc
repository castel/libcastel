#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Undefined;

bool Undefined::operatorBoolCast( void )
{
    return false;
}

runtime::Box * Undefined::operatorEqual( runtime::Box * operand )
{
    bool isOperandUndefined = dynamic_cast< runtime::boxes::Undefined * >( operand ) != nullptr;
    return runtime::helper::create< runtime::boxes::Boolean >( isOperandUndefined );
}

runtime::Box * Undefined::operatorNotEqual( runtime::Box * operand )
{
    bool isOperandNotUndefined = dynamic_cast< runtime::boxes::Undefined * >( operand ) == nullptr;
    return runtime::helper::create< runtime::boxes::Boolean >( isOperandNotUndefined );
}
