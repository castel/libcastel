#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Unary.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

#define OPERATOR( X, Y ) std::make_pair( ast::expr::Unary::Operator::X, Y )
static std::map< ast::expr::Unary::Operator, char const * > const operatorsTable {

    OPERATOR( PreIncrementation, "Castel_Operator_preIncrementation" ),
    OPERATOR( PreDecrementation, "Castel_Operator_preDecrementation" ),

    OPERATOR( PostIncrementation, "Castel_Operator_postIncrementation" ),
    OPERATOR( PostDecrementation, "Castel_Operator_postDecrementation" ),

    OPERATOR( Positive, "Castel_Operator_positive" ),
    OPERATOR( Negative, "Castel_Operator_negative" ),

    OPERATOR( BitwiseNot, "Castel_Operator_bitwiseNot" ),

};

void GPEVisitor::visit( ast::expr::Unary & unaryExpressionAst )
{
    ast::Expression * operandAst = unaryExpressionAst.operand( );

    if ( operandAst == nullptr )
        throw std::runtime_error( "Missing operand" );

    llvm::Value * operand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * operandAst );
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, operatorsTable.at( unaryExpressionAst.type( ) ), operand );
}
