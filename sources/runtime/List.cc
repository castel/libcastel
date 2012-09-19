#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/List.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::List;

runtime::Box * List::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * List::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * List::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * List::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * List::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * List::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * List::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::equalOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( static_cast< runtime::List * >( operand ) == this );
}

runtime::Box * List::notEqualOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( static_cast< runtime::List * >( operand ) != this );
}

runtime::Box * List::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * List::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * List::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool List::booleanOperator( void )
{
    return true;
}
