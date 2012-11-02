#include "castel/ast/expr/Class.hh"
#include "castel/builder/ClassBuilder.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Class & astClassExpression )
{
    mLLVMValue = builder::ClassBuilder( "literal" )
        .members( astClassExpression.members( ) )
    .create( mScope );
}
