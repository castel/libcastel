#pragma once

#include "castel/runtime/String.hh"

extern "C"
{
    castel::runtime::String * castelString_create( char const * string );
}
