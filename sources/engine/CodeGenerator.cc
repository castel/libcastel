#include <llvm/Support/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "p9/ast/Token.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

CodeGenerator::CodeGenerator ( engine::GenerationEngine & generationEngine )
: mGenerationEngine          ( generationEngine  )
, mLLVMHelpers               ( mGenerationEngine )
{
}

llvm::Value * CodeGenerator::codegen( ast::Token & token )
{
    token.accept( *this );

    return mValue.release( );
}
