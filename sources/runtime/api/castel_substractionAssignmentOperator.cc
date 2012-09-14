#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_substractionAssignmentOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->substractionAssignmentOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "substraction assignment", leftOperand, rightOperand );

    return result;
}
