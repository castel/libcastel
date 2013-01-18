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

void * castel_malloc( std::size_t size, unsigned int count )
{
    return malloc( size * count );
}

void castel_addMember( castel::runtime::Box * instance, char const * name, castel::runtime::Box * value )
{
    instance->attribute( std::make_pair( castel::runtime::Box::PropertyNS::Standards, name ), castel::runtime::helper::create< castel::runtime::attributes::Member >( value ) );
}

void castel_addMethod( castel::runtime::Box * instance, char const * name, castel::runtime::boxes::Function * function )
{
    instance->attribute( std::make_pair( castel::runtime::Box::PropertyNS::Standards, name ), castel::runtime::helper::create< castel::runtime::attributes::Method >( function ) );
}

castel::runtime::Attribute * castel_getAttribute( castel::runtime::Box * instance, castel::runtime::Box * operand )
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

castel::runtime::Box * castel_getProperty( castel::runtime::Box * instance, castel::runtime::Box * operand )
{
    return ::castel_getAttribute( instance, operand )->get( instance );
}

castel::runtime::Box * castel_setProperty( castel::runtime::Box * instance, castel::runtime::Box * operand, castel::runtime::Box * value )
{
    ::castel_getAttribute( instance, operand )->set( instance, value );

    return value;
}

castel::runtime::Box * castel_new( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    auto classOperand = dynamic_cast< castel::runtime::boxes::Class * >( operand );

    if ( classOperand == nullptr )
        castel::runtime::helper::Fatal( )
            << "Trying to instanciate non-class object" << std::endl;

    return classOperand->instanciate( argc, argv );
}

bool castel_operatorBool( castel::runtime::Box * operand )
{
    return operand->operatorBool( );
}

castel::runtime::Box * castel_operatorNumericPlus( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPlus( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "plus", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericMinus( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericMinus( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "minus", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPreIncrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPreIncrementation( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "pre-incrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPreDecrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPreDecrementation( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "pre-decrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPostIncrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPostIncrementation( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "post-incrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPostDecrementation( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPostDecrementation( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "post-decrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericAddition( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericAddition( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "addition", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericSubstraction( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericSubstraction( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "substraction", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericMultiplication( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericMultiplication( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "multiplication", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericDivision( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericDivision( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "division", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericModulo( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericModulo( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "modulo", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonLesser( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonLesser( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "lesser than", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonGreater( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonGreater( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "greater than", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonLesserOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonLesserOrEqual( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "lesser or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonGreaterOrEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonGreaterOrEqual( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "greater or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonEqual( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonNotEqual( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonNotEqual( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "not equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryNot( castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorBinaryNot( );

    if ( ret == nullptr )
        ::unaryOperatorMissing( "binary not", operand );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryAnd( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryAnd( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "binary and", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryOr( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "binary or", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryXOr( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryXOr( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "binary xor", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryLShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryLShift( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "binary left shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryRShift( castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryRShift( operandB );

    if ( ret == nullptr )
        ::binaryOperatorMissing( "binary right shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorCall( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorCall( argc, argv );

    if ( ret == nullptr )
        castel::runtime::helper::Fatal( )
            << "Non-callable instance" << std::endl;

    return ret;
}

castel::runtime::Box * castel_operatorSubscript( castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorSubscript( argc, argv );

    if ( ret == nullptr )
        castel::runtime::helper::Fatal( )
            << "Non-subscriptable instance" << std::endl;

    return ret;
}
