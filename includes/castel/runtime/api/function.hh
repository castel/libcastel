#pragma once

#include "castel/runtime/Box.hh"
#include "castel/runtime/FunctionBox.hh"

extern "C"
{
    castel::runtime::FunctionBox * castelFunction_create( castel::runtime::FunctionBox::Callable callable, unsigned int arity, castel::runtime::Box *** environmentTable );
}
