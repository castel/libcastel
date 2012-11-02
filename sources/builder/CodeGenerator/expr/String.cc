#include "castel/ast/expr/String.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::String & astStringLiteral )
{
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelString_create", mContext.irBuilder( ).CreateGlobalStringPtr( astStringLiteral.rawValue( ) ) ) );
}
