#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_equalOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    runtime::Box * result = leftOperand->equalOperator( rightOperand );

    if ( ! result )
        castel_binaryOperatorMissing( "equal", leftOperand, rightOperand );

    return result;
}
