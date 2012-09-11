#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::decl::Variables & astVariablesDeclarationStatement )
{
    for ( auto & variable : astVariablesDeclarationStatement.variables( ) )
        mClosureStack.top( )->declare( variable.name( ) );

    if ( astVariablesDeclarationStatement.next( ) ) {
        astVariablesDeclarationStatement.next( )->accept( * this );
    }
}
