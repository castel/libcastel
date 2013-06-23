#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/LSEVisitor.hh"

using namespace castel;
using gen::LSEVisitor;

void LSEVisitor::visit( ast::expr::Binary const & binaryExpressionAst )
{
    if ( binaryExpressionAst.type( ) != ast::expr::Binary::Operator::Member ) {
        this->defaultAction( binaryExpressionAst );
        return ;
    }

    ast::tools::Hold< ast::Expression > const & leftOperandAst = binaryExpressionAst.leftOperand( );
    ast::tools::Hold< ast::Expression > const & rightOperandAst = binaryExpressionAst.rightOperand( );

    if ( leftOperandAst && rightOperandAst )
        throw std::runtime_error( "Both operands missing" );

    if ( leftOperandAst )
        throw std::runtime_error( "Missing left operand" );

    if ( rightOperandAst )
        throw std::runtime_error( "Missing right operand" );

    llvm::Value * object = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * leftOperandAst );
    llvm::Value * property = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * rightOperandAst );
    gen::helper::call( mContext, mModule, mIRBuilder, "Castel_setProperty", object, property, mValue );
}
