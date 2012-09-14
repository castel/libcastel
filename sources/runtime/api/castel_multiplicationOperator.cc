#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_multiplicationOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->multiplicationOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "multiplication", leftOperand, rightOperand );

    return result;
}
