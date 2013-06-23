#include "castel/ast/expr/literal/Null.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::literal::Null const & nullLiteralAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Null_create" );
}
