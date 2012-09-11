#include "castel/runtime/Box.hh"
#include "castel/runtime/Boolean.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Boolean;

runtime::Box * Boolean::additionOperator( runtime::Box * )
{
    castel_crash( "Booleans cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Boolean::substractionOperator( runtime::Box * )
{
    castel_crash( "Booleans cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Boolean::multiplicationOperator( runtime::Box * )
{
    castel_crash( "Booleans cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Boolean::divisionOperator( runtime::Box * )
{
    castel_crash( "Booleans cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Boolean::moduloOperator( runtime::Box * )
{
    castel_crash( "Booleans cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Boolean::callOperator( unsigned int, runtime::Box ** )
{
    castel_crash( "Booleans are not callables" );

    return nullptr;
}

bool Boolean::booleanOperator( void )
{
    return mBoolean;
}
