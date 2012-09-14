#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_divisionAssignmentOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->divisionAssignmentOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "division assignment", leftOperand, rightOperand );

    return result;
}
