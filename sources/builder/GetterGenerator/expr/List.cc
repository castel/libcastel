#include "castel/ast/expr/List.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::List & astListLiteral )
{
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelList_create" );
}
