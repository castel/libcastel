#include <cstddef>

#include "castel/runtime/boxes/Binding.hh"
#include "castel/runtime/boxes/Bool.hh"
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
    #include "castel/runtime/capi.def"
    #undef CASTEL_FUNCTION

}
