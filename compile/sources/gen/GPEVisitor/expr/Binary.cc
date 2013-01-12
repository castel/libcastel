#include <map>
#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/LSEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

#define OPERATOR( X, Y ) std::make_pair( ast::expr::Binary::Operator::X, Y )
static std::map< ast::expr::Binary::Operator, char const * > const operatorsTable {

    OPERATOR( Member, "castel_getProperty" ),

    OPERATOR( NumericAddition, "castel_operatorNumericAddition" ),
    OPERATOR( NumericSubstraction, "castel_operatorNumericSubstraction" ),
    OPERATOR( NumericMultiplication, "castel_operatorNumericMultiplication" ),
    OPERATOR( NumericDivision, "castel_operatorNumericDivision" ),
    OPERATOR( NumericModulo, "castel_operatorNumericModulo" ),

    OPERATOR( NumericAssignmentAddition, "castel_operatorNumericAssignmentAddition" ),
    OPERATOR( NumericAssignmentSubstraction, "castel_operatorNumericAssignmentSubstraction" ),
    OPERATOR( NumericAssignmentMultiplication, "castel_operatorNumericAssignmentMultiplication" ),
    OPERATOR( NumericAssignmentDivision, "castel_operatorNumericAssignmentDivision" ),
    OPERATOR( NumericAssignmentModulo, "castel_operatorNumericAssignmentModulo" ),

    OPERATOR( BinaryAnd, "castel_operatorBinaryAnd" ),
    OPERATOR( BinaryOr, "castel_operatorBinaryOr" ),
    OPERATOR( BinaryXOr, "castel_operatorBinaryXOr" ),
    OPERATOR( BinaryLShift, "castel_operatorBinaryLShift" ),
    OPERATOR( BinaryRShift, "castel_operatorBinaryRShift" ),

    OPERATOR( BinaryAssignmentAnd, "castel_operatorBinaryAssignmentAnd" ),
    OPERATOR( BinaryAssignmentOr, "castel_operatorBinaryAssignmentOr" ),
    OPERATOR( BinaryAssignmentXOr, "castel_operatorBinaryAssignmentXOr" ),
    OPERATOR( BinaryAssignmentLShift, "castel_operatorBinaryAssignmentLShift" ),
    OPERATOR( BinaryAssignmentRShift, "castel_operatorBinaryAssignmentRShift" ),

    OPERATOR( ComparisonLesser, "castel_operatorComparisonLesser" ),
    OPERATOR( ComparisonGreater, "castel_operatorComparisonGreater" ),
    OPERATOR( ComparisonLesserOrEqual, "castel_operatorComparisonLesserOrEqual" ),
    OPERATOR( ComparisonGreaterOrEqual, "castel_operatorComparisonGreaterOrEqual" ),
    OPERATOR( ComparisonEqual, "castel_operatorComparisonEqual" ),
    OPERATOR( ComparisonNotEqual, "castel_operatorComparisonNotEqual" ),

};

void GPEVisitor::visit( ast::expr::Binary & binaryExpressionAst )
{
    ast::Expression * leftOperandAst = binaryExpressionAst.leftOperand( );
    ast::Expression * rightOperandAst = binaryExpressionAst.rightOperand( );

    if ( leftOperandAst == nullptr && rightOperandAst == nullptr )
        throw std::runtime_error( "Both operands missing" );

    if ( leftOperandAst == nullptr )
        throw std::runtime_error( "Left operand missing" );

    if ( rightOperandAst == nullptr )
        throw std::runtime_error( "Right operand missing" );

    if ( binaryExpressionAst.type( ) == ast::expr::Binary::Operator::Assignment ) {

        mLastReturnedValue = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * rightOperandAst );
        gen::LSEVisitor( mContext, mModule, mIRBuilder, mScope, mLastReturnedValue ).run( * leftOperandAst );

    } else {

        llvm::Value * leftOperand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * leftOperandAst );
        llvm::Value * rightOperand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * rightOperandAst );

        mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, operatorsTable.at( binaryExpressionAst.type( ) ), leftOperand, rightOperand );

    }

}
