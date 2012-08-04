#include <stdexcept>

#include "castel/ast/stmt/Expression.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::stmt::Expression & astExpressionStatement )
{
    if ( ! astExpressionStatement.expression( ) )
        throw std::runtime_error( "Missing expression" );

    astExpressionStatement.expression( )->accept( *this );
    mValue.release( );

    if ( astExpressionStatement.next( ) ) {
        astExpressionStatement.next( )->accept( *this );
    }
}
