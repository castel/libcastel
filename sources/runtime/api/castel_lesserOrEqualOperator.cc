#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_lesserOrEqualOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->lesserOrEqualOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "lesser/equal", leftOperand, rightOperand );

    return result;
}
