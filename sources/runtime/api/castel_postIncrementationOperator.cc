#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_postIncrementationOperator( runtime::Box * operand )
{
    runtime::Box * result = operand->postIncrementationOperator( );

    if ( ! result )
        castel_unaryOperatorMissing( "postincrementation", operand );

    return result;
}
