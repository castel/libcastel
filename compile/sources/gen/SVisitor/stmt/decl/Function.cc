#include "castel/ast/stmt/decl/Function.hh"
#include "castel/gen/FunctionBuilder.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::decl::Function const & functionDeclarationAst )
{
    mScope.declare( mIRBuilder, functionDeclarationAst.name( ) );

    mScope.set( mIRBuilder, functionDeclarationAst.name( ), gen::FunctionBuilder( functionDeclarationAst.name( ) )
        .parameters( & functionDeclarationAst.literal( )->parameters( ) )
        .statements( & functionDeclarationAst.literal( )->statements( ) )
    .build( mContext, mModule, mIRBuilder, mScope ) );
}
