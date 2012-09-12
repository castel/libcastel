#include "castel/runtime/Box.hh"
#include "castel/runtime/Function.hh"
#include "castel/runtime/api/function.hh"

castel::runtime::Function * castelFunction_create( castel::runtime::Box *** environmentTable, castel::runtime::Function::InternalFunction function, unsigned int arity )
{
    return castel::runtime::Function::create( environmentTable, function, arity );
}
