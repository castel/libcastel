#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>

#include "castel/ast/expr/Number.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Number & numberExpressionAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelNumber_create",
        llvm::ConstantFP::get( mContext, llvm::APFloat( numberExpressionAst.value( ) ) ) );
}
