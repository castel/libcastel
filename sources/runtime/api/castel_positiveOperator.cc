#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_positiveOperator( runtime::Box * operand )
{
    runtime::Box * result = operand->positiveOperator( );

    if ( ! result )
        castel_unaryOperatorMissing( "positive", operand );

    return result;
}
