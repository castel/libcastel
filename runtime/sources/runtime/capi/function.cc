#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/capi/function.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/Context.hh"

castel::runtime::boxes::Function * castelFunction_create( castel::runtime::Context * context, castel::runtime::boxes::Function::Signature * functionPtr, unsigned int argumentCount, castel::runtime::Box *** environment )
{
    return context->create< castel::runtime::boxes::Function >( functionPtr, argumentCount, environment );
}
