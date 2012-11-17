#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Null.hh"

using namespace castel;
using runtime::boxes::Null;

bool Null::operatorBool( runtime::Context * )
{
    return false;
}

runtime::Box * Null::operatorLogicalEqual( runtime::Context * context, runtime::Box * operand )
{
    bool isOperandNull = dynamic_cast< runtime::boxes::Null * >( operand ) != nullptr;
    return context->create< runtime::boxes::Bool >( isOperandNull );
}

runtime::Box * Null::operatorLogicalNotEqual( runtime::Context * context, runtime::Box * operand )
{
    bool isOperandNotNull = dynamic_cast< runtime::boxes::Null * >( operand ) == nullptr;
    return context->create< runtime::boxes::Bool >( isOperandNotNull );
}
