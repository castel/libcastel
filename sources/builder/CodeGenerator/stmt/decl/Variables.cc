#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::decl::Variables & astVariablesDeclarationStatement )
{
    for ( auto & variable : astVariablesDeclarationStatement.variables( ) ) {
        if ( variable.initializer( ) ) {
            variable.initializer( )->accept( * this );
            mClosureStack.top( )->declare( variable.name( ), mValue.release( ) );
        } else {
            mClosureStack.top( )->declare( variable.name( ) );
        }
    }

    if ( astVariablesDeclarationStatement.next( ) ) {
        astVariablesDeclarationStatement.next( )->accept( * this );
    }
}
