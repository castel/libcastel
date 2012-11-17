#pragma once

#include "castel/runtime/boxes/Function.hh"

extern "C" {

    castel::runtime::boxes::Function * castelFunction_create( castel::runtime::Context * context, castel::runtime::boxes::Function::Signature * functionPtr, unsigned int argumentCount, castel::runtime::Box *** environment );

}
