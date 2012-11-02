#include <stdexcept>

#include "castel/ast/stmt/Expression.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::Expression & astExpressionStatement )
{
    if ( ! astExpressionStatement.expression( ) )
        throw std::runtime_error( "Missing expression" );

    builder::GetterGenerator( mScope ).run( * ( astExpressionStatement.expression( ) ) );
}
