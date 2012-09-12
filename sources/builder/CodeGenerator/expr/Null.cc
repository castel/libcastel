#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Null.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Null & astNullExpression )
{
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelNull_create" ) );
}
