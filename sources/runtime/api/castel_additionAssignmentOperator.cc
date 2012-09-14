#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_additionAssignmentOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->additionAssignmentOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "addition assignment", leftOperand, rightOperand );

    return result;
}
