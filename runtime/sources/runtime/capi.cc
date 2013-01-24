#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>

#include "castel/runtime/attributes/Member.hh"
#include "castel/runtime/attributes/Method.hh"
#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

static void unaryOperatorMissing( char const * name, castel::runtime::Box * operand )
{
    castel::runtime::helper::Fatal( )
        << "Unary operator '" << name << "' is invalid on data type '" << "UNDEFINED" << "'" << std::endl;
}

static void binaryOperatorMissing( char const * name, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::helper::Fatal( )
        << "Binary operator '" << name << "' is invalid with data types '" << "UNDEFINED" << "' and '" << "UNDEFINED" << "'" << std::endl;
}

void * Castel_malloc( std::size_t size, unsigned int count )
{
    return malloc( size * count );
}

void Castel_addMember( castel::runtime::Box * instance, char const * name, castel::runtime::Box * value )
{
    instance->attribute( std::make_pair( castel::runtime::Box::PropertyNS::Standards, name ), castel::runtime::helper::create< castel::runtime::attributes::Member >( value ) );
}

void Castel_addMethod( castel::runtime::Box * instance, char const * name, castel::runtime::boxes::Function * function )
{
    instance->attribute( std::make_pair( castel::runtime::Box::PropertyNS::Standards, name ), castel::runtime::helper::create< castel::runtime::attributes::Method >( function ) );
}

castel::runtime::Attribute * Castel_getAttribute( castel::runtime::Box * instance, castel::runtime::Box * operand )
{
    std::string propertyName = dynamic_cast< castel::runtime::boxes::String * >( operand )->value( );
    auto key = std::make_pair( castel::runtime::Box::PropertyNS::Standards, std::string( propertyName ) );

    castel::runtime::Attribute * attribute = nullptr;

    castel::runtime::Box * currentContainer = instance;
    castel::runtime::boxes::Class * nextContainer = instance->type( );

    while ( currentContainer != nullptr && attribute == nullptr ) {
        attribute = currentContainer->attribute( key );
        currentContainer = nextContainer;
        nextContainer = nextContainer
            ? nextContainer->parent( )
            : nullptr
        ;
    }

    if ( ! attribute )
        castel::runtime::helper::Fatal( )
            << "Cannot read property '" << propertyName << "'" << std::endl;

    return attribute;
}

castel::runtime::Box * Castel_getProperty( castel::runtime::Box * instance, castel::runtime::Box * operand )
{
    return Castel_getAttribute( instance, operand )->get( instance );
}

castel::runtime::Box * Castel_setProperty( castel::runtime::Box * instance, castel::runtime::Box * operand, castel::runtime::Box * value )
{
    Castel_getAttribute( instance, operand )->set( instance, value );

    return value;
}

bool Castel_Operator_boolCast( castel::runtime::Box * operand )
{
    return operand->operatorBoolCast( );
}

castel::runtime::Box * Castel_Operator_positive( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorPositive( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "positive", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_negative( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNegative( );

    if ( ret == nullptr )
        unaryOperatorMissing( "negative", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_preIncrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorPreIncrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "pre-incrementation", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_preDecrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorPreDecrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "pre-decrementation", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_postIncrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorPostIncrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "post-incrementation", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_postDecrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorPostDecrementation( );

    if ( ret == nullptr )
        unaryOperatorMissing( "post-decrementation", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_addition( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorAddition( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "addition", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_substraction( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorSubstraction( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "substraction", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_multiplication( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorMultiplication( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "multiplication", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_division( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorDivision( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "division", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_modulo( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorModulo( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "modulo", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_bitwiseNot( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorBitwiseNot( );

    if ( ret == nullptr )
        unaryOperatorMissing( "bitwise not", operand );

    return ret;
}

castel::runtime::Box * Castel_Operator_bitwiseAnd( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBitwiseAnd( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "bitwise and", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_bitwiseOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBitwiseOr( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "bitwise or", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_bitwiseXOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBitwiseXOr( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "bitwise xor", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_leftShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorLeftShift( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "left shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_rightShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorRightShift( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "right shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_lesser( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorLesser( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "lesser than", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_greater( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorGreater( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "greater than", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_lesserOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorLesserOrEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "lesser or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_greaterOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorGreaterOrEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "greater or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_equal( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_notEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNotEqual( operandB );

    if ( ret == nullptr )
        binaryOperatorMissing( "not equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * Castel_Operator_subscript( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorSubscript( argc, argv );

    if ( ret == nullptr )
        castel::runtime::helper::Fatal( )
            << "Non-subscriptable operator" << std::endl;

    return ret;
}

castel::runtime::Box * Castel_Operator_call( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorCall( argc, argv );

    if ( ret == nullptr )
        castel::runtime::helper::Fatal( )
            << "Non-callable operator" << std::endl;

    return ret;
}

castel::runtime::Box * Castel_Operator_new( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorNew( argc, argv );

    if ( ret == nullptr )
        castel::runtime::helper::Fatal( )
            << "Non-instanciable operator" << std::endl;

    return ret;
}

castel::runtime::Box * Castel_Operator_require( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorRequire( argc, argv );

    if ( ret == nullptr )
        castel::runtime::helper::Fatal( )
            << "Non-requirable operator" << std::endl;

    return ret;
}
