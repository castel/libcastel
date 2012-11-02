#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Bool.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

void GetterGenerator::visit( ast::expr::Bool & astBoolExpression )
{
    llvm::Value * llvmLLVMValue = astBoolExpression.value( ) ? llvm::ConstantInt::getTrue( mContext.llvmContext( ) ) : llvm::ConstantInt::getFalse( mContext.llvmContext( ) );
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( "castelBool_create", llvmLLVMValue );
}
