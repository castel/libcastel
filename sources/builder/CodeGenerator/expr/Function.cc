#include "castel/ast/expr/Function.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/FunctionBuilder.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Function & astFunctionExpression )
{
    mValue.reset( builder::FunctionBuilder( "literal" )
        .parameters( astFunctionExpression.parameters( ) )
        .statements( astFunctionExpression.statements( ) )
    .create( mScope ) );
}
