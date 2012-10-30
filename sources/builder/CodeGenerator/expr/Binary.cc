#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

static std::map< ast::expr::Binary::Operator, char const * > const operatorsTable {

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
    if ( ! astBinaryExpression.leftOperand( ) )
        throw std::runtime_error( "Missing left operand" );

    if ( ! astBinaryExpression.rightOperand( ) )
        throw std::runtime_error( "Missing right operand" );

    if ( astBinaryExpression.type( ) == ast::expr::Binary::Operator::Assignment ) {

        ast::expr::Variable * astVariable = dynamic_cast< ast::expr::Variable * >( astBinaryExpression.leftOperand( ) );

        if ( ! astVariable )
            throw std::runtime_error( "Invalid lvalue" );

        astBinaryExpression.rightOperand( )->accept( *this );
        mScope.set( astVariable->name( ), mValue.get( ) );

    } else {

        astBinaryExpression.leftOperand( )->accept( * this );
        llvm::Value * llvmLeftOperand = mValue.release( );

        astBinaryExpression.rightOperand( )->accept( * this );
        llvm::Value * llvmRightOperand = mValue.release( );

        mValue.reset( mContext.irBuilder().CreateCastelCall( operatorsTable.at( astBinaryExpression.type( ) ), llvmLeftOperand, llvmRightOperand ) );

    }

}
