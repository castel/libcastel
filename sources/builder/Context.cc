#include <llvm/Function.h>

#include "castel/builder/Context.hh"

using namespace castel;
using builder::Context;

void Context::registerFunctions( void )
{
    #define TO_STRING( X ) #X
    #define REGISTER_FUNCTION( NAME ) this->declareGlobalFunction< decltype( ::NAME ) >( TO_STRING( NAME ), llvm::GlobalValue::ExternalLinkage );

        REGISTER_FUNCTION( castel_malloc );

        REGISTER_FUNCTION( castel_fatal );

        REGISTER_FUNCTION( castel_unaryOperatorMissing );
        REGISTER_FUNCTION( castel_binaryOperatorMissing );

        REGISTER_FUNCTION( castel_addMember );
        REGISTER_FUNCTION( castel_addMethod );

        REGISTER_FUNCTION( castel_getProperty );
        REGISTER_FUNCTION( castel_setProperty );

        REGISTER_FUNCTION( castel_new );

        REGISTER_FUNCTION( castel_operatorNumericPlus );
        REGISTER_FUNCTION( castel_operatorNumericMinus );

        REGISTER_FUNCTION( castel_operatorNumericPreIncrementation );
        REGISTER_FUNCTION( castel_operatorNumericPreDecrementation );
        REGISTER_FUNCTION( castel_operatorNumericPostIncrementation );
        REGISTER_FUNCTION( castel_operatorNumericPostDecrementation );

        REGISTER_FUNCTION( castel_operatorNumericAddition );
        REGISTER_FUNCTION( castel_operatorNumericSubstraction );
        REGISTER_FUNCTION( castel_operatorNumericMultiplication );
        REGISTER_FUNCTION( castel_operatorNumericDivision );
        REGISTER_FUNCTION( castel_operatorNumericModulo );

        REGISTER_FUNCTION( castel_operatorComparisonLesser );
        REGISTER_FUNCTION( castel_operatorComparisonGreater );
        REGISTER_FUNCTION( castel_operatorComparisonLesserOrEqual );
        REGISTER_FUNCTION( castel_operatorComparisonGreaterOrEqual );
        REGISTER_FUNCTION( castel_operatorComparisonEqual );
        REGISTER_FUNCTION( castel_operatorComparisonNotEqual );

        REGISTER_FUNCTION( castel_operatorBinaryNot );
        REGISTER_FUNCTION( castel_operatorBinaryAnd );
        REGISTER_FUNCTION( castel_operatorBinaryOr );
        REGISTER_FUNCTION( castel_operatorBinaryXOr );
        REGISTER_FUNCTION( castel_operatorBinaryLShift );
        REGISTER_FUNCTION( castel_operatorBinaryRShift );

        REGISTER_FUNCTION( castel_operatorCall );
        REGISTER_FUNCTION( castel_operatorSubscript );

        REGISTER_FUNCTION( castel_operatorBool );

        REGISTER_FUNCTION( castelBool_create );
        REGISTER_FUNCTION( castelClass_create );
        REGISTER_FUNCTION( castelDict_create );
        REGISTER_FUNCTION( castelFunction_create );
        REGISTER_FUNCTION( castelList_create );
        REGISTER_FUNCTION( castelNull_create );
        REGISTER_FUNCTION( castelNumber_create );
        REGISTER_FUNCTION( castelString_create );
        REGISTER_FUNCTION( castelUndefined_create );

    #undef REGISTER_FUNCTION
    #undef TO_STRING
}
