#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_postDecrementationOperator( runtime::Box * operand )
{
    runtime::Box * result = operand->postDecrementationOperator( );

    if ( ! result )
        castel_unaryOperatorMissing( "postdecrementation", operand );

    return result;
}
