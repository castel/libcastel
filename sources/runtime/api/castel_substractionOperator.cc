#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_substractionOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->substractionOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "substraction", leftOperand, rightOperand );

    return result;
}
