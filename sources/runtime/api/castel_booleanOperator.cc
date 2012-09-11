#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

bool castel_booleanOperator( runtime::Box * operand )
{
    return operand->booleanOperator( );
}
