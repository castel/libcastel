#include "castel/ast/expr/Class.hh"
#include "castel/gen/ClassBuilder.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Class & classExpressionAst )
{
    mLastReturnedValue = gen::ClassBuilder( "literal" )
        .members( classExpressionAst.members( ) )
    .build( mContext, mModule, mIRBuilder, mScope );
}
