#include "castel/runtime/Box.hh"
#include "castel/runtime/api.hh"

using namespace castel;

runtime::Box * castel_subscriptOperator( runtime::Box * operand, unsigned int argc, runtime::Box ** argv )
{
    return operand->subscriptOperator( argc, argv );
}
