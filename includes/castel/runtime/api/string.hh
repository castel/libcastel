#pragma once

#include "castel/runtime/StringBox.hh"

extern "C"
{
    castel::runtime::StringBox * castelString_create( char const * value );
}
