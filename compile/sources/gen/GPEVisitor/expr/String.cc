#include "castel/ast/expr/String.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/string.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::String & stringLiteralAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelString_create",
        gen::helper::string( mIRBuilder, stringLiteralAst.rawValue( ) ) );
}
