#pragma once

#include "castel/runtime/Boolean.hh"

extern "C"
{
    castel::runtime::Boolean * castelBoolean_create( castel::runtime::Boolean::InternalBoolean boolean );
}
