#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/SetterGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

static std::map< ast::expr::Binary::Operator, char const * > const operatorsTable {

    std::make_pair( ast::expr::Binary::Operator::Member, "castel_getProperty" ),

    std::make_pair( ast::expr::Binary::Operator::NumericAddition, "castel_operatorNumericAddition" ),
    std::make_pair( ast::expr::Binary::Operator::NumericSubstraction, "castel_operatorNumericSubstraction" ),
    std::make_pair( ast::expr::Binary::Operator::NumericMultiplication, "castel_operatorNumericMultiplication" ),
    std::make_pair( ast::expr::Binary::Operator::NumericDivision, "castel_operatorNumericDivision" ),
    std::make_pair( ast::expr::Binary::Operator::NumericModulo, "castel_operatorNumericModulo" ),

    std::make_pair( ast::expr::Binary::Operator::NumericAssignmentAddition, "castel_operatorNumericAssignmentAddition" ),
    std::make_pair( ast::expr::Binary::Operator::NumericAssignmentSubstraction, "castel_operatorNumericAssignmentSubstraction" ),
    std::make_pair( ast::expr::Binary::Operator::NumericAssignmentMultiplication, "castel_operatorNumericAssignmentMultiplication" ),
    std::make_pair( ast::expr::Binary::Operator::NumericAssignmentDivision, "castel_operatorNumericAssignmentDivision" ),
    std::make_pair( ast::expr::Binary::Operator::NumericAssignmentModulo, "castel_operatorNumericAssignmentModulo" ),

    std::make_pair( ast::expr::Binary::Operator::BinaryAnd, "castel_operatorBinaryAnd" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryOr, "castel_operatorBinaryOr" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryXOr, "castel_operatorBinaryXOr" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryLShift, "castel_operatorBinaryLShift" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryRShift, "castel_operatorBinaryRShift" ),

    std::make_pair( ast::expr::Binary::Operator::BinaryAssignmentAnd, "castel_operatorBinaryAssignmentAnd" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryAssignmentOr, "castel_operatorBinaryAssignmentOr" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryAssignmentXOr, "castel_operatorBinaryAssignmentXOr" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryAssignmentLShift, "castel_operatorBinaryAssignmentLShift" ),
    std::make_pair( ast::expr::Binary::Operator::BinaryAssignmentRShift, "castel_operatorBinaryAssignmentRShift" ),

    std::make_pair( ast::expr::Binary::Operator::ComparisonLesser, "castel_operatorComparisonLesser" ),
    std::make_pair( ast::expr::Binary::Operator::ComparisonGreater, "castel_operatorComparisonGreater" ),
    std::make_pair( ast::expr::Binary::Operator::ComparisonLesserOrEqual, "castel_operatorComparisonLesserOrEqual" ),
    std::make_pair( ast::expr::Binary::Operator::ComparisonGreaterOrEqual, "castel_operatorComparisonGreaterOrEqual" ),
    std::make_pair( ast::expr::Binary::Operator::ComparisonEqual, "castel_operatorComparisonEqual" ),
    std::make_pair( ast::expr::Binary::Operator::ComparisonNotEqual, "castel_operatorComparisonNotEqual" ),

};

void CodeGenerator::visit( ast::expr::Binary & astBinaryExpression )
{
    ast::Expression * astLeftOperand = astBinaryExpression.leftOperand( );
    ast::Expression * astRightOperand = astBinaryExpression.rightOperand( );

    if ( astLeftOperand == nullptr && astRightOperand == nullptr )
        throw std::runtime_error( "Both operands missing" );

    if ( astLeftOperand == nullptr )
        throw std::runtime_error( "Left operand missing" );

    if ( astRightOperand == nullptr )
        throw std::runtime_error( "Right operand missing" );

    if ( astBinaryExpression.type( ) == ast::expr::Binary::Operator::Assignment ) {

        llvm::Value * llvmValue = builder::CodeGenerator( mContext, mScope ).expression( * astRightOperand );
        mValue.reset( builder::SetterGenerator( mContext, mScope ).expression( * astLeftOperand, llvmValue ) );

    } else {

        llvm::Value * llvmLeftOperand = builder::CodeGenerator( mContext, mScope ).expression( * astLeftOperand );
        llvm::Value * llvmRightOperand = builder::CodeGenerator( mContext, mScope ).expression( * astRightOperand );

        mValue.reset( mContext.irBuilder( ).CreateCastelCall( operatorsTable.at( astBinaryExpression.type( ) ), llvmLeftOperand, llvmRightOperand ) );

    }

}
