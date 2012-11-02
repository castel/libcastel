#include "castel/ast/expr/Undefined.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Undefined & astUndefinedExpression )
{
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelUndefined_create" );
}
