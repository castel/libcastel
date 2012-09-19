#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/ListBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::ListBox;

runtime::Box * ListBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * ListBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * ListBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * ListBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * ListBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * ListBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * ListBox::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::equalOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( static_cast< runtime::ListBox * >( operand ) == this );
}

runtime::Box * ListBox::notEqualOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( static_cast< runtime::ListBox * >( operand ) != this );
}

runtime::Box * ListBox::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * ListBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * ListBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool ListBox::booleanOperator( void )
{
    return true;
}
