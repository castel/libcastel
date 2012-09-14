#include "castel/runtime/Box.hh"
#include "castel/runtime/Boolean.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Boolean;

runtime::Box * Boolean::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * Boolean::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * Boolean::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Boolean::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Boolean::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Boolean::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Boolean::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::equalOperator( runtime::Box * operand )
{
    runtime::Boolean * booleanOperand = dynamic_cast< runtime::Boolean * >( operand );

    if ( ! booleanOperand )
        return nullptr;

    return runtime::Boolean::create( mBoolean == booleanOperand->mBoolean );
}

runtime::Box * Boolean::notEqualOperator( runtime::Box * operand )
{
    runtime::Boolean * booleanOperand = dynamic_cast< runtime::Boolean * >( operand );

    if ( ! booleanOperand )
        return nullptr;

    return runtime::Boolean::create( mBoolean != booleanOperand->mBoolean );
}

runtime::Box * Boolean::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Boolean::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Boolean::accessOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool Boolean::booleanOperator( void )
{
    return mBoolean;
}
