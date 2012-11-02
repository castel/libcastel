#include "castel/ast/expr/String.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::String & astStringLiteral )
{
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelString_create", mContext.irBuilder( ).CreateGlobalStringPtr( astStringLiteral.rawValue( ) ) );
}
