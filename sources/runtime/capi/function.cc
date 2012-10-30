#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/capi/function.hh"
#include "castel/runtime/Box.hh"

castel::runtime::boxes::Function * castelFunction_create( castel::runtime::boxes::Function::Signature * functionPtr, unsigned int argumentCount, castel::runtime::Box *** environment )
{
    return castel::runtime::boxes::Function::create( functionPtr, argumentCount, environment );
}
