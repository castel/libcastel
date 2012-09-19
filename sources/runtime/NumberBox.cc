#include <cmath>

#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/NumberBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::NumberBox;

runtime::Box * NumberBox::positiveOperator( void )
{
    return runtime::NumberBox::create( + mValue );
}

runtime::Box * NumberBox::negativeOperator( void )
{
    return runtime::NumberBox::create( - mValue );
}

runtime::Box * NumberBox::preIncrementationOperator( void )
{
    mValue += 1.0;

    return this;
}

runtime::Box * NumberBox::postIncrementationOperator( void )
{
    runtime::NumberBox * save = runtime::NumberBox::create( mValue );

    mValue += 1.0;

    return save;
}

runtime::Box * NumberBox::preDecrementationOperator( void )
{
    mValue -= 1.0;

    return this;
}

runtime::Box * NumberBox::postDecrementationOperator( void )
{
    runtime::NumberBox * save = runtime::NumberBox::create( mValue );

    mValue -= 1.0;

    return save;
}

runtime::Box * NumberBox::additionOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::NumberBox::create( mValue + numberOperand->mValue );
}

runtime::Box * NumberBox::substractionOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::NumberBox::create( mValue - numberOperand->mValue );
}

runtime::Box * NumberBox::multiplicationOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::NumberBox::create( mValue * numberOperand->mValue );
}

runtime::Box * NumberBox::divisionOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::NumberBox::create( mValue / numberOperand->mValue );
}

runtime::Box * NumberBox::moduloOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::NumberBox::create( static_cast< int >( mValue ) % static_cast< int >( numberOperand->mValue ) );
}

runtime::Box * NumberBox::lesserOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue < numberOperand->mValue );
}

runtime::Box * NumberBox::greaterOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue > numberOperand->mValue );
}

runtime::Box * NumberBox::lesserOrEqualOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue <= numberOperand->mValue );
}

runtime::Box * NumberBox::greaterOrEqualOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue >= numberOperand->mValue );
}


runtime::Box * NumberBox::equalOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue == numberOperand->mValue );
}

runtime::Box * NumberBox::notEqualOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::BooleanBox::create( mValue != numberOperand->mValue );
}

runtime::Box * NumberBox::additionAssignmentOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::NumberBox::create( mValue + numberOperand->mValue );
}

runtime::Box * NumberBox::substractionAssignmentOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue = mValue - numberOperand->mValue;

    return this;
}

runtime::Box * NumberBox::multiplicationAssignmentOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue = mValue * numberOperand->mValue;

    return this;
}

runtime::Box * NumberBox::divisionAssignmentOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue = mValue / numberOperand->mValue;

    return this;
}

runtime::Box * NumberBox::moduloAssignmentOperator( runtime::Box * operand )
{
    runtime::NumberBox * numberOperand = dynamic_cast< runtime::NumberBox * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mValue = static_cast< int >( mValue ) % static_cast< int >( numberOperand->mValue );

    return this;
}

runtime::Box * NumberBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * NumberBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool NumberBox::booleanOperator( void )
{
    return ! std::isnan( mValue ) && mValue != 0.0;
}
