#include <map>
#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/LSEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

#define OPERATOR( X, Y ) std::make_pair( ast::expr::Binary::Operator::X, Y )
static std::map< ast::expr::Binary::Operator, char const * > const operatorsTable {

    OPERATOR( Member, "Castel_getProperty" ),

    OPERATOR( Addition, "Castel_Operator_addition" ),
    OPERATOR( Substraction, "Castel_Operator_substraction" ),
    OPERATOR( Multiplication, "Castel_Operator_multiplication" ),
    OPERATOR( Division, "Castel_Operator_division" ),
    OPERATOR( Modulo, "Castel_Operator_modulo" ),

    OPERATOR( BitwiseAnd, "Castel_Operator_bitwiseAnd" ),
    OPERATOR( BitwiseOr, "Castel_Operator_bitwiseOr" ),
    OPERATOR( BitwiseXOr, "Castel_Operator_bitwiseXOr" ),
    OPERATOR( LeftShift, "Castel_Operator_leftShift" ),
    OPERATOR( RightShift, "Castel_Operator_rightShift" ),

    OPERATOR( Lesser, "Castel_Operator_lesser" ),
    OPERATOR( Greater, "Castel_Operator_greater" ),
    OPERATOR( LesserOrEqual, "Castel_Operator_lesserOrEqual" ),
    OPERATOR( GreaterOrEqual, "Castel_Operator_greaterOrEqual" ),
    OPERATOR( Equal, "Castel_Operator_equal" ),
    OPERATOR( NotEqual, "Castel_Operator_notEqual" ),

};

void GPEVisitor::visit( ast::expr::Binary const & binaryExpressionAst )
{
    ast::tools::Hold< ast::Expression > const & leftOperandAst = binaryExpressionAst.leftOperand( );
    ast::tools::Hold< ast::Expression > const & rightOperandAst = binaryExpressionAst.rightOperand( );

    if ( leftOperandAst && rightOperandAst )
        throw std::runtime_error( "Binary operators must have both operands when built as general purpose expressions" );

    if ( leftOperandAst )
        throw std::runtime_error( "Binary operators must have both operands when built as general purpose expressions (left missing)" );

    if ( rightOperandAst )
        throw std::runtime_error( "Binary operators must have both operands when built as general purpose expressions (right missing)" );

    if ( binaryExpressionAst.type( ) == ast::expr::Binary::Operator::Assignment ) {

        mLastReturnedValue = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * rightOperandAst );
        gen::LSEVisitor( mContext, mModule, mIRBuilder, mScope, mLastReturnedValue ).run( * leftOperandAst );

    } else {

        llvm::Value * leftOperand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * leftOperandAst );
        llvm::Value * rightOperand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * rightOperandAst );

        mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, operatorsTable.at( binaryExpressionAst.type( ) ), leftOperand, rightOperand );

    }

}
