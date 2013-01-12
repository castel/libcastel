#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Bool.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Bool & boolExpressionAst )
{
    llvm::Value * value = boolExpressionAst.value( ) ? llvm::ConstantInt::getTrue( mContext ) : llvm::ConstantInt::getFalse( mContext );
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelBool_create", value );
}
