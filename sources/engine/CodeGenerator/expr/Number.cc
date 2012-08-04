#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>

#include "castel/ast/expr/Number.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::expr::Number & number )
{
    mValue.reset( mLLVMHelpers.doubleToBox( number.value( ) ) );
}
