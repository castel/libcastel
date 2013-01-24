#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>

#include "castel/ast/expr/literal/Number.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::literal::Number & numberLiteralAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Number_create",
        llvm::ConstantFP::get( mContext, llvm::APFloat( numberLiteralAst.value( ) ) ) );
}
