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

    void * castel_malloc( castel::runtime::Context * context, std::size_t size, unsigned int count );

    void castel_fatal( castel::runtime::Context * context, char const * errorMessage );

    void castel_unaryOperatorMissing( castel::runtime::Context * context, char const * name, castel::runtime::Box * operand );

    void castel_binaryOperatorMissing( castel::runtime::Context * context, char const * name, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    void castel_addMember( castel::runtime::Context * context, castel::runtime::Box * instance, char const * name, castel::runtime::Box * value );

    void castel_addMethod( castel::runtime::Context * context, castel::runtime::Box * instance, char const * name, castel::runtime::boxes::Function * function );

    castel::runtime::Box * castel_getProperty( castel::runtime::Context * context, castel::runtime::Box * instance, castel::runtime::Box * name );

    castel::runtime::Box * castel_setProperty( castel::runtime::Context * context, castel::runtime::Box * instance, castel::runtime::Box * name, castel::runtime::Box * value );

    castel::runtime::Box * castel_new( castel::runtime::Context * context, castel::runtime::Box * instance, unsigned int argc, castel::runtime::Box ** argv );

    bool castel_operatorBool( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPlus( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericMinus( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPreIncrementation( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPreDecrementation( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPostIncrementation( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericPostDecrementation( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorNumericAddition( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericSubstraction( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericMultiplication( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericDivision( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorNumericModulo( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonLesser( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonGreater( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonLesserOrEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonGreaterOrEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorComparisonNotEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryNot( castel::runtime::Context * context, castel::runtime::Box * operand );

    castel::runtime::Box * castel_operatorBinaryAnd( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryOr( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryXOr( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryLShift( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorBinaryRShift( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB );

    castel::runtime::Box * castel_operatorCall( castel::runtime::Context * context, castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );

    castel::runtime::Box * castel_operatorSubscript( castel::runtime::Context * context, castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv );

}

#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/Box.hh"
