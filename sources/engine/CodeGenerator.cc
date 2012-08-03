#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/Value.h>

#include "p9/ast/Statement.hh"
#include "p9/engine/CodeGenerator.hh"
#include "p9/utils/mpllvmExtensions.hh"

using namespace p9;
using namespace p9::engine;

CodeGenerator::CodeGenerator ( engine::GenerationEngine & generationEngine                                                   )
: mGenerationEngine          ( generationEngine                                                                              )
, mLLVMHelpers               ( mGenerationEngine.llvmContext( ), mGenerationEngine.irBuilder( ), mGenerationEngine.module( ) )
{
}

llvm::Function * CodeGenerator::codegen( ast::Statement & astStatement )
{
    llvm::Type * returnType = mpllvm::get< engine::Value * >( mGenerationEngine.llvmContext( ) );
    llvm::FunctionType * functionType = llvm::FunctionType::get( returnType, { }, false );

    llvm::Function * llvmFunction = llvm::Function::Create( functionType, llvm::Function::ExternalLinkage, "", & mGenerationEngine.module( ) );

    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "", llvmFunction );
    mGenerationEngine.irBuilder( ).SetInsertPoint( basicBlock );

    engine::Closure closure( mGenerationEngine, llvmFunction );
    mClosureStack.push( & closure );

    astStatement.accept( * this );
    mValue.release( );

    mClosureStack.pop( );
    closure.finalize( );

    mGenerationEngine.module( ).dump();
    llvm::verifyFunction( * llvmFunction );

    return llvmFunction;
}
