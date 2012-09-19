#include "castel/runtime/Box.hh"
#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::BooleanBox;

runtime::Box * BooleanBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * BooleanBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * BooleanBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * BooleanBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * BooleanBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * BooleanBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * BooleanBox::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::equalOperator( runtime::Box * operand )
{
    runtime::BooleanBox * booleanOperand = dynamic_cast< runtime::BooleanBox * >( operand );

    if ( ! booleanOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue == booleanOperand->mValue );
}

runtime::Box * BooleanBox::notEqualOperator( runtime::Box * operand )
{
    runtime::BooleanBox * booleanOperand = dynamic_cast< runtime::BooleanBox * >( operand );

    if ( ! booleanOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue != booleanOperand->mValue );
}

runtime::Box * BooleanBox::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * BooleanBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * BooleanBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool BooleanBox::booleanOperator( void )
{
    return mValue;
}
