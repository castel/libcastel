#include <llvm/Value.h>

#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::decl::Variables const & variablesDeclarationStatementAst )
{
    for ( auto const & variable : variablesDeclarationStatementAst.variables( ) ) {

        mScope.declare( mIRBuilder, variable->name( ) );

        ast::tools::Hold< ast::Expression > const & initializerAst = variable->initializer( );
        if ( initializerAst ) {
            llvm::Value * initializer = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * initializerAst );
            mScope.set( mIRBuilder, variable->name( ), initializer );
        }

    }
}
