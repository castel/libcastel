#include "castel/ast/expr/Undefined.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Undefined & undefinedExpressionAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelUndefined_create" );
}
