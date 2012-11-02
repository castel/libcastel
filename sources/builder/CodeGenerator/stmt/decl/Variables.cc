#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::decl::Variables & astVariablesDeclarationStatement )
{
    for ( auto & variable : astVariablesDeclarationStatement.variables( ) ) {

        ast::Expression * astInitializer = variable.initializer( );

        mScope.declare( variable.name( ) );

        if ( astInitializer != nullptr ) {
            llvm::Value * llvmValue = builder::GetterGenerator( mScope ).run( * astInitializer );
            mScope.set( variable.name( ), llvmValue );
        }

    }
}
