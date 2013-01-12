#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Null;

bool Null::operatorBool( void )
{
    return false;
}

runtime::Box * Null::operatorLogicalEqual( runtime::Box * operand )
{
    bool isOperandNull = dynamic_cast< runtime::boxes::Null * >( operand ) != nullptr;
    return runtime::helper::create< runtime::boxes::Bool >( isOperandNull );
}

runtime::Box * Null::operatorLogicalNotEqual( runtime::Box * operand )
{
    bool isOperandNotNull = dynamic_cast< runtime::boxes::Null * >( operand ) == nullptr;
    return runtime::helper::create< runtime::boxes::Bool >( isOperandNotNull );
}
