#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_additionOperator( runtime::Box * leftOperand, runtime::Box * rightOperand )
{
    return leftOperand->additionOperator( rightOperand );
}
