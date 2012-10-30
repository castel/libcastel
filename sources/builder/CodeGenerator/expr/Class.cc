#include "castel/ast/expr/Class.hh"
#include "castel/builder/ClassBuilder.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Class & astClassExpression )
{
    mValue.reset( builder::ClassBuilder( "literal" )
        .members( astClassExpression.members( ) )
    .create( mScope ) );
}
