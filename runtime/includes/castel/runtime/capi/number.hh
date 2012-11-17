#pragma once

#include "castel/runtime/boxes/Number.hh"

extern "C" {

    castel::runtime::boxes::Number * castelNumber_create( castel::runtime::Context * context, double value );

}
