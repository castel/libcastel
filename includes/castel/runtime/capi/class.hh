#pragma once

#include "castel/runtime/boxes/Class.hh"

extern "C" {

    castel::runtime::boxes::Class * castelClass_create( castel::runtime::boxes::Class * parent, castel::runtime::boxes::Class::InitializerSignature * initializer, castel::runtime::Box *** environment );

}
