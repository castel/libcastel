#include "castel/runtime/Box.hh"
#include "castel/runtime/Function.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Function;

runtime::Box * Function::additionOperator( runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::substractionOperator( runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::multiplicationOperator( runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::divisionOperator( runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::moduloOperator( runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::callOperator( unsigned int argc, runtime::Box ** argv )
{
    return mFunction( mEnvironmentTable, argc, argv );
}

bool Function::booleanOperator( void )
{
    return true;
}
