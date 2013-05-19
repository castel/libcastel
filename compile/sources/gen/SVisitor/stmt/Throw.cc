#include "castel/ast/stmt/Throw.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/null.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::Throw & throwStatementAst )
{
    ast::Expression * expression = throwStatementAst.expression( );

    gen::helper::call( mContext, mModule, mIRBuilder, "Castel_throw", expression
        ? gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * expression )
        : gen::helper::null( gen::helper::type< runtime::Box * >( mContext ) ) );

    mIRBuilder.CreateUnreachable( );
}
