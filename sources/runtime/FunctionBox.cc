#include "castel/runtime/BooleanBox.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/FunctionBox.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::FunctionBox;

runtime::Box * FunctionBox::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * FunctionBox::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * FunctionBox::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * FunctionBox::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * FunctionBox::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * FunctionBox::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * FunctionBox::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::equalOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( this == operand );
}

runtime::Box * FunctionBox::notEqualOperator( runtime::Box * operand )
{
    return runtime::BooleanBox::create( this != operand );
}

runtime::Box * FunctionBox::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * FunctionBox::callOperator( unsigned int argc, runtime::Box ** argv )
{
    if ( argc < mArity )
        castel_crash( "Bad argument count in function call" );

    return mCallable( mEnvironmentTable, argc, argv );
}

runtime::Box * FunctionBox::subscriptOperator( unsigned int, runtime::Box ** )
{
    return nullptr;
}

bool FunctionBox::booleanOperator( void )
{
    return true;
}
