#include "castel/ast/expr/Variable.hh"
#include "castel/gen/LSEVisitor.hh"

using namespace castel;
using gen::LSEVisitor;

void LSEVisitor::visit( ast::expr::Variable const & variableExpressionAst )
{
    mScope.set( mIRBuilder, variableExpressionAst.name( ), mValue );
}
