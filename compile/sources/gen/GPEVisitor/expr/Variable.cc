#include "castel/ast/expr/Variable.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Variable const & variableExpressionAst )
{
    mLastReturnedValue = mScope.get( mIRBuilder, variableExpressionAst.name( ) );
}
