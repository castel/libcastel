#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Dict.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Dict;

runtime::Box * Dict::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * Dict::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * Dict::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Dict::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Dict::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Dict::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Dict::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::equalOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( static_cast< runtime::Dict * >( operand ) == this );
}

runtime::Box * Dict::notEqualOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( static_cast< runtime::Dict * >( operand ) != this );
}

runtime::Box * Dict::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Dict::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * Dict::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool Dict::booleanOperator( void )
{
    return true;
}
