#include "p9/ast/stmt/Expression.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::stmt::Expression & astExpressionStatement )
{
    if ( astExpressionStatement.next( ) ) {
        astExpressionStatement.next( )->accept( *this );
    }
}
