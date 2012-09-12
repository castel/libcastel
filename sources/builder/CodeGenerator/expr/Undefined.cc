#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Undefined.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Undefined & astUndefinedExpression )
{
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelUndefined_create" ) );
}
