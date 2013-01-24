#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/LSEVisitor.hh"

using namespace castel;
using gen::LSEVisitor;

void LSEVisitor::visit( ast::expr::Binary & binaryExpressionAst )
{
    if ( binaryExpressionAst.type( ) != ast::expr::Binary::Operator::Member )
        this->defaultAction( binaryExpressionAst );

    ast::Expression * leftOperandAst = binaryExpressionAst.leftOperand( );
    ast::Expression * rightOperandAst = binaryExpressionAst.rightOperand( );

    if ( leftOperandAst == nullptr && rightOperandAst == nullptr )
        throw std::runtime_error( "Both operands missing" );

    if ( leftOperandAst == nullptr )
        throw std::runtime_error( "Missing left operand" );

    if ( rightOperandAst == nullptr )
        throw std::runtime_error( "Missing right operand" );

    llvm::Value * object = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * leftOperandAst );
    llvm::Value * property = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * rightOperandAst );
    gen::helper::call( mContext, mModule, mIRBuilder, "Castel_setProperty", object, property, mValue );
}
