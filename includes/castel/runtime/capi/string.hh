#pragma once

#include "castel/runtime/boxes/String.hh"

extern "C" {

    castel::runtime::boxes::String * castelString_create( char const * value );

}
