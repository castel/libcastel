#include "castel/ast/expr/Function.hh"
#include "castel/builder/GetterGenerator.hh"
#include "castel/builder/FunctionBuilder.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Function & astFunctionExpression )
{
    mLLVMValue = builder::FunctionBuilder( "literal" )
        .parameters( astFunctionExpression.parameters( ) )
        .statements( astFunctionExpression.statements( ) )
    .create( mScope );
}
