#include <stdexcept>

#include "castel/ast/expr/Variable.hh"
#include "castel/builder/SetterGenerator.hh"

using namespace castel;
using builder::SetterGenerator;

void SetterGenerator::visit( ast::expr::Variable & astVariableExpression )
{
    mScope.set( astVariableExpression.name( ), mValue.release( ) );
}
