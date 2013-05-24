#include <cstdint>
#include <iostream>

#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/interface.hh"

using namespace castel;

static void unaryOperatorMissing( char const * name, runtime::Box * operand )
{
    runtime::helper::Fatal( )
        << "Unary operator '" << name << "' is invalid on data type '" << "UNDEFINED" << "'" << std::endl;
}

static void binaryOperatorMissing( char const * name, runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::helper::Fatal( )
        << "Binary operator '" << name << "' is invalid with data types '" << "UNDEFINED" << "' and '" << "UNDEFINED" << "'" << std::endl;
}

bool Castel_Operator_boolCast( runtime::Box * operand )
{
    return operand->operatorBoolCast( );
}

runtime::Box * Castel_Operator_positive( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorPositive( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "positive", operand );

    return ret;
}

runtime::Box * Castel_Operator_negative( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorNegative( );

    if ( ret == nullptr )
        unaryOperatorMissing( "negative", operand );

    return ret;
}

runtime::Box * Castel_Operator_preIncrementation( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorPreIncrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "pre-incrementation", operand );

    return ret;
}

runtime::Box * Castel_Operator_preDecrementation( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorPreDecrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "pre-decrementation", operand );

    return ret;
}

runtime::Box * Castel_Operator_postIncrementation( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorPostIncrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "post-incrementation", operand );

    return ret;
}

runtime::Box * Castel_Operator_postDecrementation( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorPostDecrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "post-decrementation", operand );

    return ret;
}

runtime::Box * Castel_Operator_addition( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorAddition( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "addition", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_substraction( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorSubstraction( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "substraction", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_multiplication( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorMultiplication( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "multiplication", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_division( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorDivision( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "division", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_modulo( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorModulo( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "modulo", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_bitwiseNot( runtime::Box * operand )
{
    runtime::Box * ret = operand->operatorBitwiseNot( );

    if ( ret == nullptr )
        unaryOperatorMissing( "bitwise not", operand );

    return ret;
}

runtime::Box * Castel_Operator_bitwiseAnd( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorBitwiseAnd( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "bitwise and", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_bitwiseOr( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorBitwiseOr( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "bitwise or", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_bitwiseXOr( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorBitwiseXOr( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "bitwise xor", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_leftShift( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorLeftShift( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "left shift", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_rightShift( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorRightShift( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "right shift", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_lesser( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorLesser( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "lesser than", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_greater( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorGreater( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "greater than", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_lesserOrEqual( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorLesserOrEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "lesser or equal", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_greaterOrEqual( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorGreaterOrEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "greater or equal", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_equal( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "equal", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_notEqual( runtime::Box * operandA, runtime::Box * operandB )
{
    runtime::Box * ret = operandA->operatorNotEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "not equal", operandA, operandB );

    return ret;
}

runtime::Box * Castel_Operator_subscript( runtime::Box * operand, std::uint32_t argc, runtime::Box ** argv )
{
    runtime::Box * ret = operand->operatorSubscript( argc, argv );

    if ( ret == nullptr )
        runtime::helper::Fatal( )
            << "Non-subscriptable operator" << std::endl;

    return ret;
}

runtime::Box * Castel_Operator_call( runtime::Box * operand, std::uint32_t argc, runtime::Box ** argv )
{
    runtime::Box * ret = operand->operatorCall( argc, argv );

    if ( ret == nullptr )
        runtime::helper::Fatal( )
            << "Non-callable operator" << std::endl;

    return ret;
}

runtime::Box * Castel_Operator_new( runtime::Box * operand, std::uint32_t argc, runtime::Box ** argv )
{
    runtime::Box * ret = operand->operatorNew( argc, argv );

    if ( ret == nullptr )
        runtime::helper::Fatal( )
            << "Non-instanciable operator" << std::endl;

    return ret;
}

runtime::Box * Castel_Operator_require( runtime::Box * operand, std::uint32_t argc, runtime::Box ** argv )
{
    runtime::Box * ret = operand->operatorRequire( argc, argv );

    if ( ret == nullptr )
        runtime::helper::Fatal( )
            << "Non-requirable operator" << std::endl;

    return ret;
}
