#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Unary.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

#define OPERATOR( X, Y ) std::make_pair( ast::expr::Unary::Operator::X, Y )
static std::map< ast::expr::Unary::Operator, char const * > const operatorsTable {

    OPERATOR( NumericPreIncrementation, "castel_operatorNumericPreIncrementation" ),
    OPERATOR( NumericPreDecrementation, "castel_operatorNumericPreDecrementation" ),

    OPERATOR( NumericPostIncrementation, "castel_operatorNumericPostIncrementation" ),
    OPERATOR( NumericPostDecrementation, "castel_operatorNumericPostDecrementation" ),

    OPERATOR( NumericPlus, "castel_operatorNumericPlus" ),
    OPERATOR( NumericMinus, "castel_operatorNumericMinus" ),

    OPERATOR( BinaryNot, "castel_operatorBinaryNot" ),

};

void GPEVisitor::visit( ast::expr::Unary & unaryExpressionAst )
{
    ast::Expression * operandAst = unaryExpressionAst.operand( );

    if ( operandAst == nullptr )
        throw std::runtime_error( "Missing operand" );

    llvm::Value * operand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * operandAst );
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, operatorsTable.at( unaryExpressionAst.type( ) ), operand );
}
