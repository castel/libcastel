#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/UndefinedBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::UndefinedBox;

runtime::Box * UndefinedBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * UndefinedBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * UndefinedBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * UndefinedBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * UndefinedBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * UndefinedBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * UndefinedBox::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::equalOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( dynamic_cast< runtime::UndefinedBox * >( operand ) ? true : false );
}

runtime::Box * UndefinedBox::notEqualOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( dynamic_cast< runtime::UndefinedBox * >( operand ) ? false : true );
}

runtime::Box * UndefinedBox::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * UndefinedBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * UndefinedBox::subscriptOperator( unsigned, runtime::Box ** )
{
    return nullptr;
}

bool UndefinedBox::booleanOperator( void )
{
    return false;
}
