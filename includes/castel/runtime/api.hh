#pragma once

#include "castel/runtime/Box.hh"

extern "C"
{

    void * castel_allocate( unsigned int count, unsigned int size );

    void castel_crash( char const * message );

    castel::runtime::Box * castel_additionOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_substractionOperator   ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_multiplicationOperator ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_divisionOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_moduloOperator         ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );

    castel::runtime::Box * castel_callOperator   ( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );
    castel::runtime::Box * castel_accessOperator ( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );

}
