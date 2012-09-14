#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_additionOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->additionOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "addition", leftOperand, rightOperand );

    return result;
}
