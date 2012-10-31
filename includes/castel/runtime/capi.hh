#include <cstddef>

namespace castel
{

    namespace runtime
    {

        class Box;

        namespace boxes
        {

            class Function;

        }

    }

}

extern "C" {

    void * castel_malloc( std::size_t size, unsigned int count );

    void castel_fatal( char const * errorMessage );

    void castel_unaryOperatorMissing( char const * name, castel::runtime::Box * operand );

    void castel_binaryOperatorMissing( char const * name, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    void castel_addMember( castel::runtime::Box * instance, char const * name, castel::runtime::Box * value );

    void castel_addMethod( castel::runtime::Box * instance, char const * name, castel::runtime::boxes::Function * function );

    castel::runtime::Box * castel_getProperty( castel::runtime::Box * instance, castel::runtime::Box * name );

    castel::runtime::Box * castel_setProperty( castel::runtime::Box * instance, castel::runtime::Box * name, castel::runtime::Box * value );

    castel::runtime::Box * castel_new( castel::runtime::Box * instance, unsigned int argc, castel::runtime::Box ** argv );

    bool castel_operatorBool( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPlus( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericMinus( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPreIncrementation( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPreDecrementation( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPostIncrementation( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPostDecrementation( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericAddition( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericSubstraction( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericMultiplication( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericDivision( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericModulo( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonLesser( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonGreater( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonLesserOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonGreaterOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonNotEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryNot( castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorBinaryAnd( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryXOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryLShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryRShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorCall( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );

    castel::runtime::Box * castel_operatorSubscript( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );

}

#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"
