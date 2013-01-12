#include "castel/ast/expr/Null.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Null & nullExpressionAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelNull_create" );
}
