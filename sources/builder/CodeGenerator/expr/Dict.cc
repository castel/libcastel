#include "castel/ast/expr/Dict.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Dict & astDictLiteral )
{
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelDict_create" ) );
}
