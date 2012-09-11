#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>

#include "castel/ast/expr/Number.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Number & number )
{
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelNumber_create", llvm::ConstantFP::get( mContext.llvmContext( ), llvm::APFloat( number.value( ) ) ) ) );
}
