#include <stdexcept>

#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::Expression const & expressionStatementAst )
{
    ast::tools::Hold< ast::Expression > const & expressionAst = expressionStatementAst.expression( );

    if ( expressionAst )
        throw std::runtime_error( "Expression statements must have an expression when built" );

    gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * expressionAst );
}
