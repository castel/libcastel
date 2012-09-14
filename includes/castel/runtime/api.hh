#pragma once

#include "castel/runtime/Box.hh"

extern "C"
{

    void * castel_allocate( unsigned int count, unsigned int size );

    void castel_crash( char const * message );

    void castel_unaryOperatorMissing( char const * name, castel::runtime::Box * operand );
    void castel_binaryOperatorMissing( char const * name, castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );

    castel::runtime::Box * castel_positiveOperator ( castel::runtime::Box * operand );
    castel::runtime::Box * castel_negativeOperator ( castel::runtime::Box * operand );

    castel::runtime::Box * castel_preIncrementationOperator  ( castel::runtime::Box * operand );
    castel::runtime::Box * castel_postIncrementationOperator ( castel::runtime::Box * operand );
    castel::runtime::Box * castel_preDecrementationOperator  ( castel::runtime::Box * operand );
    castel::runtime::Box * castel_postDecrementationOperator ( castel::runtime::Box * operand );

    castel::runtime::Box * castel_additionOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_substractionOperator   ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_multiplicationOperator ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_divisionOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_moduloOperator         ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );

    castel::runtime::Box * castel_lesserOperator         ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_greaterOperator        ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_lesserOrEqualOperator  ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_greaterOrEqualOperator ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_equalOperator          ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_notEqualOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );

    castel::runtime::Box * castel_additionAssignmentOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_substractionAssignmentOperator   ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_multiplicationAssignmentOperator ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_divisionAssignmentOperator       ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );
    castel::runtime::Box * castel_moduloAssignmentOperator         ( castel::runtime::Box * leftOperand, castel::runtime::Box * rightOperand );

    castel::runtime::Box * castel_callOperator   ( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );
    castel::runtime::Box * castel_accessOperator ( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );

    bool castel_booleanOperator ( castel::runtime::Box * operand );

}
