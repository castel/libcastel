#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_greaterOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->greaterOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "greater", leftOperand, rightOperand );

    return result;
}
