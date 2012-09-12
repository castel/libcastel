#include "castel/runtime/Box.hh"
#include "castel/runtime/Null.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Null;

runtime::Box * Null::additionOperator( runtime::Box * )
{
    castel_crash( "Null values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Null::substractionOperator( runtime::Box * )
{
    castel_crash( "Null values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Null::multiplicationOperator( runtime::Box * )
{
    castel_crash( "Null values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Null::divisionOperator( runtime::Box * )
{
    castel_crash( "Null values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Null::moduloOperator( runtime::Box * )
{
    castel_crash( "Null values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Null::callOperator( unsigned int, runtime::Box ** )
{
    castel_crash( "Null values are not callables" );

    return nullptr;
}

bool Null::booleanOperator( void )
{
    return false;
}
