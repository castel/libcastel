#include <stdexcept>

#include "castel/ast/stmt/Expression.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::Expression & expressionStatementAst )
{
    ast::Expression * expressionAst = expressionStatementAst.expression( );

    if ( expressionAst == nullptr )
        throw std::runtime_error( "Missing expression" );

    gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * expressionAst );
}
