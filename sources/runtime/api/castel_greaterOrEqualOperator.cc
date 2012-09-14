#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_greaterOrEqualOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->greaterOrEqualOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "greater/equal", leftOperand, rightOperand );

    return result;
}
