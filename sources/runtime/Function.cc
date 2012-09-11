#include "castel/runtime/Box.hh"
#include "castel/runtime/Function.hh"
#include "castel/runtime/api.hh"

using namespace castel;
using runtime::Function;

runtime::Box * Function::additionOperator( runtime::Box ***, runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::substractionOperator( runtime::Box ***, runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::multiplicationOperator( runtime::Box ***, runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::divisionOperator( runtime::Box ***, runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::moduloOperator( runtime::Box ***, runtime::Box * )
{
    castel_crash( "Functions cannot be used as operands in arithmetic expressions" );

    return nullptr;
}

runtime::Box * Function::callOperator( runtime::Box *** environment, unsigned int argc, runtime::Box ** argv )
{
    return mFunction( environment, argc, argv );
}
