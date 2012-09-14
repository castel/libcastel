#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_preIncrementationOperator( runtime::Box * operand )
{
    runtime::Box * result = operand->preIncrementationOperator( );

    if ( ! result )
        castel_unaryOperatorMissing( "preincrementation", operand );

    return result;
}
