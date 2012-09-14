#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Null.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Null;

runtime::Box * Null::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * Null::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * Null::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Null::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Null::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Null::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Null::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::equalOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( dynamic_cast< runtime::Null * >( operand ) ? true : false );
}

runtime::Box * Null::notEqualOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( dynamic_cast< runtime::Null * >( operand ) ? false : true );
}

runtime::Box * Null::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Null::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool Null::booleanOperator( void )
{
    return false;
}
