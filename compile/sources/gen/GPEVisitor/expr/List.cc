#include "castel/ast/expr/List.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::List & listLiteralAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelList_create" );
}
