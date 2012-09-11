#include "castel/runtime/Function.hh"
#include "castel/runtime/api/function.hh"

castel::runtime::Function * castelFunction_create( castel::runtime::Function::InternalFunction function )
{
    return castel::runtime::Function::create( function );
}
