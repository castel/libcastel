#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Boolean.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Boolean & astBooleanExpression )
{
    llvm::Value * booleanValue = astBooleanExpression.value( ) ? llvm::ConstantInt::getTrue( mContext.llvmContext( ) ) : llvm::ConstantInt::getFalse( mContext.llvmContext( ) );
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelBoolean_create", booleanValue ) );
}
