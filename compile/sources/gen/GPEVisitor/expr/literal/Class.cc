#include "castel/ast/expr/literal/Class.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/ClassBuilder.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::literal::Class const & classLiteralAst )
{
    ast::tools::Hold< ast::Expression > const & parent = classLiteralAst.parent( );

    mLastReturnedValue = gen::ClassBuilder( "literal" )
        .parent( parent ? gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * parent ) : nullptr )
        .members( & classLiteralAst.members( ) )
    .build( mContext, mModule, mIRBuilder, mScope );
}
