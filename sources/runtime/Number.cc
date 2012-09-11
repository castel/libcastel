#include "castel/runtime/Box.hh"
#include "castel/runtime/Number.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Number;

runtime::Box * Number::additionOperator( runtime::Box ***, runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return runtime::Number::create( );

    return runtime::Number::create( mNumber + numberOperand->mNumber );
}

runtime::Box * Number::substractionOperator( runtime::Box ***, runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return runtime::Number::create( );

    return runtime::Number::create( mNumber - numberOperand->mNumber );
}

runtime::Box * Number::multiplicationOperator( runtime::Box ***, runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return runtime::Number::create( );

    return runtime::Number::create( mNumber * numberOperand->mNumber );
}

runtime::Box * Number::divisionOperator( runtime::Box ***, runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return runtime::Number::create( );

    return runtime::Number::create( mNumber / numberOperand->mNumber );
}

runtime::Box * Number::moduloOperator( runtime::Box ***, runtime::Box * operand )
{
    runtime::Number * numberOperand = dynamic_cast< runtime::Number * >( operand );

    if ( ! numberOperand )
        return runtime::Number::create( );

    return runtime::Number::create( static_cast< int >( mNumber ) % static_cast< int >( numberOperand->mNumber ) );
}

runtime::Box * Number::callOperator( runtime::Box ***, unsigned int, runtime::Box ** )
{
    castel_crash( "Numbers are not callables" );

    return nullptr;
}
