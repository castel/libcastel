#include <cmath>

#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Number.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Number;

runtime::Box * Number::positiveOperator( void )
{
    return runtime::Number::create( + mNumber );
}

runtime::Box * Number::negativeOperator( void )
{
    return runtime::Number::create( - mNumber );
}

runtime::Box * Number::preIncrementationOperator( void )
{
    mNumber += 1.0;

    return this;
}

runtime::Box * Number::postIncrementationOperator( void )
{
    runtime::Number * save = runtime::Number::create( mNumber );

    mNumber += 1.0;

    return save;
}

runtime::Box * Number::preDecrementationOperator( void )
{
    mNumber -= 1.0;

    return this;
}

runtime::Box * Number::postDecrementationOperator( void )
{
    runtime::Number * save = runtime::Number::create( mNumber );

    mNumber -= 1.0;

    return save;
}

runtime::Box * Number::additionOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Number::create( mNumber + numberOperand->mNumber );
}

runtime::Box * Number::substractionOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Number::create( mNumber - numberOperand->mNumber );
}

runtime::Box * Number::multiplicationOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Number::create( mNumber * numberOperand->mNumber );
}

runtime::Box * Number::divisionOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Number::create( mNumber / numberOperand->mNumber );
}

runtime::Box * Number::moduloOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Number::create( static_cast< int >( mNumber ) % static_cast< int >( numberOperand->mNumber ) );
}

runtime::Box * Number::lesserOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Boolean::create( mNumber < numberOperand->mNumber );
}

runtime::Box * Number::greaterOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Boolean::create( mNumber > numberOperand->mNumber );
}

runtime::Box * Number::lesserOrEqualOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Boolean::create( mNumber <= numberOperand->mNumber );
}

runtime::Box * Number::greaterOrEqualOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Boolean::create( mNumber >= numberOperand->mNumber );
}


runtime::Box * Number::equalOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Boolean::create( mNumber == numberOperand->mNumber );
}

runtime::Box * Number::notEqualOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Boolean::create( mNumber != numberOperand->mNumber );
}

runtime::Box * Number::additionAssignmentOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    return runtime::Number::create( mNumber + numberOperand->mNumber );
}

runtime::Box * Number::substractionAssignmentOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mNumber = mNumber - numberOperand->mNumber;

    return this;
}

runtime::Box * Number::multiplicationAssignmentOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mNumber = mNumber * numberOperand->mNumber;

    return this;
}

runtime::Box * Number::divisionAssignmentOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mNumber = mNumber / numberOperand->mNumber;

    return this;
}

runtime::Box * Number::moduloAssignmentOperator( runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return nullptr;

    mNumber = static_cast< int >( mNumber ) % static_cast< int >( numberOperand->mNumber );

    return this;
}

runtime::Box * Number::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Number::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool Number::booleanOperator( void )
{
    return ! std::isnan( mNumber ) && mNumber != 0.0;
}
