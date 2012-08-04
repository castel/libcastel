#include <llvm/Instructions.h>

#include "castel/ast/expr/Variable.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::expr::Variable & astVariableExpression )
{
    mValue.reset( mClosureStack.top( )->get( astVariableExpression.name( ) ) );
}
