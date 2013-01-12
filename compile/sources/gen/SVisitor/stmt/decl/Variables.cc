#include <llvm/Value.h>

#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::decl::Variables & variablesDeclarationStatementAst )
{
    for ( auto & variable : variablesDeclarationStatementAst.variables( ) ) {

        ast::Expression * initializerAst = variable.initializer( );

        mScope.declare( mIRBuilder, variable.name( ) );

        if ( initializerAst != nullptr ) {
            llvm::Value * initializer = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * initializerAst );
            mScope.set( mIRBuilder, variable.name( ), initializer );
        }

    }
}
