#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Type.h>

#include "p9/ast/stmt/decl/Variables.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

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
