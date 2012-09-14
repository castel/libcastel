#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_notEqualOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->notEqualOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "not equal", leftOperand, rightOperand );

    return result;
}
