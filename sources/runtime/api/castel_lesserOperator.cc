#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_lesserOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->lesserOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "lesser", leftOperand, rightOperand );

    return result;
}
