#include <llvm/IR/Constants.h>
#include <llvm/IR/Value.h>

#include "castel/ast/expr/literal/Boolean.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::literal::Boolean const & booleanLiteralAst )
{
    llvm::Value * value = booleanLiteralAst.value( ) ? llvm::ConstantInt::getTrue( mContext ) : llvm::ConstantInt::getFalse( mContext );
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Boolean_create", value );
}
