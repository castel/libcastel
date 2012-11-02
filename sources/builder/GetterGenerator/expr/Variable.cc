#include "castel/ast/expr/Variable.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Variable & astVariableExpression )
{
    mLLVMValue = mScope.get( astVariableExpression.name( ) );
}
