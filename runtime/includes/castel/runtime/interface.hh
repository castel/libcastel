#pragma once

#include <cstdint>

#include "castel/runtime/interfaces/all.prelude.hh"
#include "castel/runtime/Box.hh"

extern "C" {

    #define CASTEL_FUNCTION( NAME, RETURN, PARAMETERS ) \
        RETURN NAME PARAMETERS;

    #define CASTEL_TYPE( TYPE, CONSTRUCTOR )                                                                      \
        CASTEL_FUNCTION( Castel_##TYPE##_create, castel::runtime::boxes::TYPE *, CONSTRUCTOR )                    \
        CASTEL_FUNCTION( Castel_##TYPE##_initialize, castel::runtime::boxes::TYPE *, ( castel::runtime::Box * ) )

    #define CASTEL_SHIPPED_FUNCTION( TYPE, NAME )                                                                                               \
        CASTEL_FUNCTION( Castel_##TYPE##_##NAME, castel::runtime::Box *, ( castel::runtime::Box ***, std::uint32_t, castel::runtime::Box ** ) )

    #include "castel/runtime/interfaces/all.def"

    #undef CASTEL_SHIPPED_FUNCTION

    #undef CASTEL_TYPE

    #undef CASTEL_FUNCTION

}
