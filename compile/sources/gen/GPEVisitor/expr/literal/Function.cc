#include "castel/ast/expr/literal/Function.hh"
#include "castel/gen/FunctionBuilder.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::literal::Function const & functionLiteralAst )
{
    mLastReturnedValue = gen::FunctionBuilder( "literal" )
        .parameters( & functionLiteralAst.parameters( ) )
        .statements( & functionLiteralAst.statements( ) )
    .build( mContext, mModule, mIRBuilder, mScope );
}
