#include <llvm/Instructions.h>

#include "p9/ast/expr/Variable.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Variable & astVariableExpression )
{
    llvm::AllocaInst * variable = mScopes.top( )->get( astVariableExpression.name( ) );

    mValue.reset( mGenerationEngine.builder( ).CreateLoad( variable ) );
}
