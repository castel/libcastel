#include "castel/runtime/boxes/Bool.hh"
#include "castel/runtime/boxes/Undefined.hh"

using namespace castel;
using runtime::boxes::Undefined;

bool Undefined::operatorBool( runtime::Context * )
{
    return false;
}

runtime::Box * Undefined::operatorLogicalEqual( runtime::Context * context, runtime::Box * operand )
{
    bool isOperandUndefined = dynamic_cast< runtime::boxes::Undefined * >( operand ) != nullptr;
    return context->create< runtime::boxes::Bool >( isOperandUndefined );
}

runtime::Box * Undefined::operatorLogicalNotEqual( runtime::Context * context, runtime::Box * operand )
{
    bool isOperandNotUndefined = dynamic_cast< runtime::boxes::Undefined * >( operand ) == nullptr;
    return context->create< runtime::boxes::Bool >( isOperandNotUndefined );
}
