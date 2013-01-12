#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::Box;

bool Box::operatorBool( void )
{
    return false;
}

runtime::Box * Box::operatorNumericPlus( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericMinus( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPreIncrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPreDecrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPostIncrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericPostDecrementation( void )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAddition( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericSubstraction( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericMultiplication( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericDivision( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericModulo( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentAddition( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentSubstraction( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentMultiplication( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentDivision( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorNumericAssignmentModulo( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryNot( void )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAnd( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryOr( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryXOr( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryLShift( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryRShift( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentAnd( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentOr( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentXOr( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentLShift( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorBinaryAssignmentRShift( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonLesser( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonGreater( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonLesserOrEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonGreaterOrEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorComparisonNotEqual( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Box::operatorSubscript( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Box::operatorCall( unsigned int, runtime::Box ** )
{
    return nullptr;
}
