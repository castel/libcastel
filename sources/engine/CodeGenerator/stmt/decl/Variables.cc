#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Type.h>

#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::stmt::decl::Variables & astVariablesDeclarationStatement )
{
    llvm::Function * function = mGenerationEngine.irBuilder( ).GetInsertBlock( )->getParent( );

    llvm::BasicBlock & entryBlock = function->getEntryBlock( );
    llvm::IRBuilder< > tmpBuilder( &entryBlock, entryBlock.begin( ) );

    for ( auto & variable : astVariablesDeclarationStatement.variables( ) )
        mClosureStack.top( )->declare( variable.name( ) );

    if ( astVariablesDeclarationStatement.next( ) ) {
        astVariablesDeclarationStatement.next( )->accept( *this );
    }
}
