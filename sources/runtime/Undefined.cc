#include "castel/runtime/Box.hh"
#include "castel/runtime/Undefined.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Undefined;

runtime::Box * Undefined::additionOperator( runtime::Box * )
{
    castel_crash( "Undefined values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Undefined::substractionOperator( runtime::Box * )
{
    castel_crash( "Undefined values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Undefined::multiplicationOperator( runtime::Box * )
{
    castel_crash( "Undefined values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Undefined::divisionOperator( runtime::Box * )
{
    castel_crash( "Undefined values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Undefined::moduloOperator( runtime::Box * )
{
    castel_crash( "Undefined values cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Undefined::callOperator( unsigned int, runtime::Box ** )
{
    castel_crash( "Undefined values are not callables" );

    return nullptr;
}

bool Undefined::booleanOperator( void )
{
    return false;
}
