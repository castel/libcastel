#include "castel/ast/stmt/decl/Class.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/ClassBuilder.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::decl::Class const & classDeclarationAst )
{
    ast::tools::Hold< ast::Expression > const & parent = classDeclarationAst.literal( )->parent( );

    mScope.declare( mIRBuilder, classDeclarationAst.name( ) );

    mScope.set( mIRBuilder, classDeclarationAst.name( ), gen::ClassBuilder( classDeclarationAst.name( ) )
        .parent( parent ? gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * parent ) : nullptr )
        .members( & classDeclarationAst.literal( )->members( ) )
    .build( mContext, mModule, mIRBuilder, mScope ) );
}
