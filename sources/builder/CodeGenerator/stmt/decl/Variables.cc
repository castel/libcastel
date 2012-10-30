#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::decl::Variables & astVariablesDeclarationStatement )
{
    for ( auto & variable : astVariablesDeclarationStatement.variables( ) ) {
        if ( variable.initializer( ) ) {
            mScope.declare( variable.name( ) );
            variable.initializer( )->accept( * this );
            mScope.set( variable.name( ), mValue.release( ) );
        } else {
            mScope.declare( variable.name( ) );
        }
    }

    if ( astVariablesDeclarationStatement.next( ) ) {
        astVariablesDeclarationStatement.next( )->accept( * this );
    }
}
