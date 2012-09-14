#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Undefined.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Undefined;

runtime::Box * Undefined::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * Undefined::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * Undefined::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Undefined::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Undefined::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Undefined::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Undefined::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::equalOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( dynamic_cast< runtime::Undefined * >( operand ) ? true : false );
}

runtime::Box * Undefined::notEqualOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( dynamic_cast< runtime::Undefined * >( operand ) ? false : true );
}

runtime::Box * Undefined::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Undefined::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool Undefined::booleanOperator( void )
{
    return false;
}
