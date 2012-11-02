#include "castel/ast/expr/Null.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Null & astNullExpression )
{
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelNull_create" );
}
