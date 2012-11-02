#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Bool.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Bool & astBoolExpression )
{
    llvm::Value * llvmValue = astBoolExpression.value( ) ? llvm::ConstantInt::getTrue( mContext.llvmContext( ) ) : llvm::ConstantInt::getFalse( mContext.llvmContext( ) );
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelBool_create", llvmValue ) );
}
