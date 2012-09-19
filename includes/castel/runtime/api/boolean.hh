#pragma once

#include "castel/runtime/BooleanBox.hh"

extern "C"
{
    castel::runtime::BooleanBox * castelBoolean_create( bool value );
}
