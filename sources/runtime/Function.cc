#include "castel/runtime/Boolean.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Function.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Function;

runtime::Box * Function::positiveOperator( void )
{
    return nullptr;
}

runtime::Box * Function::negativeOperator( void )
{
    return nullptr;
}

runtime::Box * Function::preIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Function::postIncrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Function::preDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Function::postDecrementationOperator( void )
{
    return nullptr;
}

runtime::Box * Function::additionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::substractionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::multiplicationOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::divisionOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::moduloOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::lesserOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::greaterOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::lesserOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::greaterOrEqualOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::equalOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( this == operand );
}

runtime::Box * Function::notEqualOperator( runtime::Box * operand )
{
    return runtime::Boolean::create( this != operand );
}

runtime::Box * Function::additionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::substractionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::multiplicationAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::divisionAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::moduloAssignmentOperator( runtime::Box * )
{
    return nullptr;
}

runtime::Box * Function::callOperator( unsigned int argc, runtime::Box ** argv )
{
    if ( argc < mArity )
        castel_crash( "Bad argument count in function call" );

    return mFunction( mEnvironmentTable, argc, argv );
}

bool Function::booleanOperator( void )
{
    return true;
}
