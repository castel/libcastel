#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_divisionOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->divisionOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "division", leftOperand, rightOperand );

    return result;
}
