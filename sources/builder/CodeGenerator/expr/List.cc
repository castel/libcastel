#include "castel/ast/expr/List.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::List & astListLiteral )
{
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelList_create" ) );
}
