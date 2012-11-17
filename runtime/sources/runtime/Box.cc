#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::Box;

bool Box::operatorBool( runtime::Context * )
{
    return false;
}

runtime::Box * Box::operatorNumericPlus( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericMinus( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPreIncrementation( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPreDecrementation( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPostIncrementation( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPostDecrementation( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAddition( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericSubstraction( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericMultiplication( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericDivision( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericModulo( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentAddition( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentSubstraction( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentMultiplication( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentDivision( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentModulo( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryNot( runtime::Context * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAnd( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryOr( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryXOr( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryLShift( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryRShift( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentAnd( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentOr( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentXOr( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentLShift( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentRShift( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonLesser( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonGreater( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonLesserOrEqual( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonGreaterOrEqual( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonEqual( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonNotEqual( runtime::Context *, runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorSubscript( runtime::Context *, unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Box::operatorCall( runtime::Context *, unsigned int, runtime::Box ** )
{
    return nullptr;
}
