#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>

#include "castel/ast/expr/Number.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Number & astNumberExpression )
{
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelNumber_create", llvm::ConstantFP::get( mContext.llvmContext( ), llvm::APFloat( astNumberExpression.value( ) ) ) );
}
