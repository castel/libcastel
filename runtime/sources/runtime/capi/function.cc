#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

castel::runtime::boxes::Function * Castel_Function_create( castel::runtime::boxes::Function::Signature * functionPtr, unsigned int argumentCount, castel::runtime::Box *** environment )
{
    return castel::runtime::helper::create< castel::runtime::boxes::Function >( functionPtr, argumentCount, environment );
}
