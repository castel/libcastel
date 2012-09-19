#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/DictBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::DictBox;

runtime::Box * DictBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * DictBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * DictBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * DictBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * DictBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * DictBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * DictBox::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::equalOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( static_cast< runtime::DictBox * >( operand ) == this );
}

runtime::Box * DictBox::notEqualOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( static_cast< runtime::DictBox * >( operand ) != this );
}

runtime::Box * DictBox::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * DictBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * DictBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool DictBox::booleanOperator( void )
{
    return true;
}
