#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_moduloAssignmentOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->moduloAssignmentOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "modulo assignment", leftOperand, rightOperand );

    return result;
}
