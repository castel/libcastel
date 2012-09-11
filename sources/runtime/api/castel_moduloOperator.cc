#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_moduloOperator( runtime::Box *** environment, runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    return leftOperand->moduloOperator( environment, rightOperand );
}
