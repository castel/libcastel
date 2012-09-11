#pragma once

#include "castel/runtime/Number.hh"

extern "C"
{
    castel::runtime::Number * castelNumber_create( castel::runtime::Number::InternalNumber number );
}
