#include "castel/ast/expr/Function.hh"
#include "castel/gen/FunctionBuilder.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Function & functionExpressionAst )
{
    mLastReturnedValue = gen::FunctionBuilder( "literal" )
        .parameters( functionExpressionAst.parameters( ) )
        .statements( functionExpressionAst.statements( ) )
    .build( mContext, mModule, mIRBuilder, mScope );
}
