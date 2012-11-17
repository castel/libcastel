#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>

#include "castel/runtime/attributes/Member.hh"
#include "castel/runtime/attributes/Method.hh"
#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/Box.hh"
#include "castel/runtime/capi.hh"

void * castel_malloc( castel::runtime::Context * context, std::size_t size, unsigned int count )
{
    return context->allocator( )->alloc( size, count );
}

void castel_fatal( castel::runtime::Context * context, char const * errorMessage )
{
    context->fatal( errorMessage );
}

void castel_unaryOperatorMissing( castel::runtime::Context * context, char const * name, castel::runtime::Box * operand )
{
    std::ostringstream stream;
    stream << "Unary operator '" << name << "' is invalid on data type '" << "UNDEFINED" << "'";
    context->fatal( stream.str( ) );
}

void castel_binaryOperatorMissing( castel::runtime::Context * context, char const * name, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    std::ostringstream stream;
    stream << "Binary operator '" << name << "' is invalid with data types '" << "UNDEFINED" << "' and '" << "UNDEFINED" << "'";
    context->fatal( stream.str( ) );
}

void castel_addMember( castel::runtime::Context * context, castel::runtime::Box * instance, char const * name, castel::runtime::Box * value )
{
    instance->attribute( std::make_pair( castel::runtime::Box::PropertyNS::Standards, name ), context->create< castel::runtime::attributes::Member >( value ) );
}

void castel_addMethod( castel::runtime::Context * context, castel::runtime::Box * instance, char const * name, castel::runtime::boxes::Function * function )
{
    instance->attribute( std::make_pair( castel::runtime::Box::PropertyNS::Standards, name ), context->create< castel::runtime::attributes::Method >( function ) );
}

castel::runtime::Attribute * castel_getAttribute( castel::runtime::Context * context, castel::runtime::Box * instance, castel::runtime::Box * operand )
{
    auto stringOperand = dynamic_cast< castel::runtime::boxes::String * >( operand );

    if ( stringOperand == nullptr )
        context->fatal( "Invalid operand to getMember()" );

    castel::runtime::Box * container = instance;
    castel::runtime::Attribute * attribute = nullptr;

    auto key = std::make_pair( castel::runtime::Box::PropertyNS::Standards, std::string( stringOperand->value( ) ) );

    while ( container != nullptr && attribute == nullptr )
        attribute = container->attribute( key ),
            container = container->type( );

    if ( ! attribute )
        context->fatal( "Property not found" );

    return attribute;
}

castel::runtime::Box * castel_getProperty( castel::runtime::Context * context, castel::runtime::Box * instance, castel::runtime::Box * operand )
{
    return ::castel_getAttribute( context, instance, operand )->get( context, instance );
}

castel::runtime::Box * castel_setProperty( castel::runtime::Context * context, castel::runtime::Box * instance, castel::runtime::Box * operand, castel::runtime::Box * value )
{
    ::castel_getAttribute( context, instance, operand )->set( context, instance, value );

    return value;
}

castel::runtime::Box * castel_new( castel::runtime::Context * context, castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    auto classOperand = dynamic_cast< castel::runtime::boxes::Class * >( operand );

    if ( classOperand == nullptr )
        context->fatal( "Trying to instanciate non-class object" );

    return classOperand->instanciate( context, argc, argv );
}

bool castel_operatorBool( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    return operand->operatorBool( context );
}

castel::runtime::Box * castel_operatorNumericPlus( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPlus( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "plus", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericMinus( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericMinus( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "minus", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPreIncrementation( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPreIncrementation( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "pre-incrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPreDecrementation( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPreDecrementation( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "pre-decrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPostIncrementation( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPostIncrementation( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "post-incrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericPostDecrementation( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorNumericPostDecrementation( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "post-decrementation", operand );

    return ret;
}

castel::runtime::Box * castel_operatorNumericAddition( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericAddition( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "addition", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericSubstraction( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericSubstraction( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "substraction", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericMultiplication( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericMultiplication( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "multiplication", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericDivision( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericDivision( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "division", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorNumericModulo( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorNumericModulo( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "modulo", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonLesser( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonLesser( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "lesser than", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonGreater( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonGreater( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "greater than", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonLesserOrEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonLesserOrEqual( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "lesser or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonGreaterOrEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonGreaterOrEqual( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "greater or equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonEqual( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorComparisonNotEqual( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorComparisonNotEqual( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "not equal", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryNot( castel::runtime::Context * context, castel::runtime::Box * operand )
{
    castel::runtime::Box * ret = operand->operatorBinaryNot( context );

    if ( ret == nullptr )
        ::castel_unaryOperatorMissing( context, "binary not", operand );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryAnd( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryAnd( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "binary and", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryOr( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryOr( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "binary or", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryXOr( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryXOr( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "binary xor", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryLShift( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryLShift( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "binary left shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorBinaryRShift( castel::runtime::Context * context, castel::runtime::Box * operandA, castel::runtime::Box * operandB )
{
    castel::runtime::Box * ret = operandA->operatorBinaryRShift( context, operandB );

    if ( ret == nullptr )
        ::castel_binaryOperatorMissing( context, "binary right shift", operandA, operandB );

    return ret;
}

castel::runtime::Box * castel_operatorCall( castel::runtime::Context * context, castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorCall( context, argc, argv );

    if ( ret == nullptr )
        context->fatal( "Non-callable instance" );

    return ret;
}

castel::runtime::Box * castel_operatorSubscript( castel::runtime::Context * context, castel::runtime::Box * operand, unsigned int argc, castel::runtime::Box ** argv )
{
    castel::runtime::Box * ret = operand->operatorSubscript( context, argc, argv );

    if ( ret == nullptr )
        context->fatal( "Non-subscriptable instance" );

    return ret;
}
