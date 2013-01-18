#include "castel/ast/expr/Class.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/ClassBuilder.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Class & classExpressionAst )
{
    ast::Expression * parent = classExpressionAst.parent( );

    mLastReturnedValue = gen::ClassBuilder( "literal" )
        .parent( parent != nullptr ? gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * parent ) : nullptr )
        .members( classExpressionAst.members( ) )
    .build( mContext, mModule, mIRBuilder, mScope );
}
