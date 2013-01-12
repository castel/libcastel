#include "castel/ast/stmt/Return.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::Return & returnStatementAst )
{
    ast::Expression * expressionAst = returnStatementAst.expression( );

    if ( expressionAst == nullptr ) {
        mIRBuilder.CreateRet( gen::helper::call( mContext, mModule, mIRBuilder, "castelUndefined_create" ) );
    } else {
        mIRBuilder.CreateRet( gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * expressionAst ) );
    }
}
