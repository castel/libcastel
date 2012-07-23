#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>

#include "p9/ast/expr/Number.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Number & number )
{
    mValue.reset( llvm::ConstantFP::get( mContext, llvm::APFloat( number.value( ) ) ) );
}
