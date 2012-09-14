#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_moduloOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->moduloOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "modulo", leftOperand, rightOperand );

    return result;
}
