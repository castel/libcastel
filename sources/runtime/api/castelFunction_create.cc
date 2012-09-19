#include "castel/runtime/Box.hh"
#include "castel/runtime/FunctionBox.hh"
#include "castel/runtime/api/function.hh"

castel::runtime::FunctionBox * castelFunction_create( castel::runtime::FunctionBox::Callable callable, unsigned int arity, castel::runtime::Box *** environmentTable )
{
    return castel::runtime::FunctionBox::create( callable, arity, environmentTable );
}
