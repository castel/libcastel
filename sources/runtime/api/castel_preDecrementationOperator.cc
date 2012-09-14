#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_preDecrementationOperator( runtime::Box * operand )
{
    runtime::Box * result = operand->preDecrementationOperator( );

    if ( ! result )
        castel_unaryOperatorMissing( "predecrementation", operand );

    return result;
}
