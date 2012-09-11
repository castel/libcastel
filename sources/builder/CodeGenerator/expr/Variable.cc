#include <llvm/Instructions.h>

#include "castel/ast/expr/Variable.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Variable & astVariableExpression )
{
    mValue.reset( mClosureStack.top( )->get( astVariableExpression.name( ) ) );
}
