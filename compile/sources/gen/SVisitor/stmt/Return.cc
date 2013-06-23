#include "castel/ast/stmt/Return.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::Return const & returnStatementAst )
{
    ast::tools::Hold< ast::Expression > const & expressionAst = returnStatementAst.expression( );

    if ( expressionAst ) {
        mIRBuilder.CreateRet( gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Undefined_create" ) );
    } else {
        mIRBuilder.CreateRet( gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * expressionAst ) );
    }
}
