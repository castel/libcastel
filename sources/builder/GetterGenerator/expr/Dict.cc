#include "castel/ast/expr/Dict.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Dict & astDictLiteral )
{
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelDict_create" );
}
