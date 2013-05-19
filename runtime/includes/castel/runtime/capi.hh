#pragma once

#include <cstdint>

#include "castel/runtime/boxes/Binding.hh"
#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/boxes/List.hh"
#include "castel/runtime/boxes/Null.hh"
#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/boxes/Object.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/boxes/Undefined.hh"
#include "castel/runtime/Box.hh"

extern "C" {

    #define CASTEL_FUNCTION( NAME, RETURN, PARAMETERS ) RETURN NAME PARAMETERS;

    #define CASTEL_TYPE( TYPE, CONSTRUCTOR ) castel::runtime::boxes::TYPE * Castel_##TYPE##_create CONSTRUCTOR; castel::runtime::Box * Castel_##TYPE##_initialize( void * );
    #define CASTEL_SHIPPED_FUNCTION( TYPE, NAME ) castel::runtime::Box * Castel_##TYPE##_##NAME( castel::runtime::Box ***, int argc, castel::runtime::Box ** argv );

    #include "castel/runtime/capi/boolean.def"
    #include "castel/runtime/capi/class.def"
    #include "castel/runtime/capi/dict.def"
    #include "castel/runtime/capi/function.def"
    #include "castel/runtime/capi/list.def"
    #include "castel/runtime/capi/null.def"
    #include "castel/runtime/capi/number.def"
    #include "castel/runtime/capi/string.def"
    #include "castel/runtime/capi/undefined.def"
    #include "castel/runtime/capi.def"

    #undef CASTEL_SHIPPED_FUNCTION
    #undef CASTEL_TYPE

    #undef CASTEL_FUNCTION

}
