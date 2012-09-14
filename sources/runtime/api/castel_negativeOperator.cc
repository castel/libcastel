#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_negativeOperator( runtime::Box * operand )
{
    runtime::Box * result = operand->negativeOperator( );

    if ( ! result )
        castel_unaryOperatorMissing( "negative", operand );

    return result;
}
