#include <cstdint>

#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

runtime::boxes::Function * Castel_Function_create( runtime::boxes::Function::Signature * functionPtr, std::int32_t argumentCount, runtime::Box *** environment )
{
    return runtime::helper::create< runtime::boxes::Function >( functionPtr, argumentCount, environment );
}
