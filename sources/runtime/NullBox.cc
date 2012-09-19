#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/NullBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::NullBox;

runtime::Box * NullBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * NullBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * NullBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * NullBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * NullBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * NullBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * NullBox::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::equalOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( dynamic_cast< runtime::NullBox * >( operand ) ? true : false );
}

runtime::Box * NullBox::notEqualOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( dynamic_cast< runtime::NullBox * >( operand ) ? false : true );
}

runtime::Box * NullBox::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * NullBox::callOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

runtime::Box * NullBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool NullBox::booleanOperator( void )
{
    return false;
}
