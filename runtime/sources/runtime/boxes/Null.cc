#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Null;

bool Null::operatorBoolCast( void )
{
    return false;
}

runtime::Box * Null::operatorEqual( runtime::Box * operand )
{
    bool isOperandNull = dynamic_cast< runtime::boxes::Null * >( operand ) != nullptr;
    return runtime::helper::create< runtime::boxes::Boolean >( isOperandNull );
}

runtime::Box * Null::operatorNotEqual( runtime::Box * operand )
{
    bool isOperandNotNull = dynamic_cast< runtime::boxes::Null * >( operand ) == nullptr;
    return runtime::helper::create< runtime::boxes::Boolean >( isOperandNotNull );
}
