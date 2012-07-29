#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
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

llvm::Function * CodeGenerator::codegen( ast::Token & token )
{
    llvm::FunctionType * functionType = llvm::FunctionType::get( llvm::PointerType::get( mGenerationEngine.boxType( ), 0 ), { }, false );
    llvm::Function * function = llvm::Function::Create( functionType, llvm::Function::ExternalLinkage, "", & mGenerationEngine.module( ) );

    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create( mGenerationEngine.context( ), "", function );
    mGenerationEngine.builder( ).SetInsertPoint( basicBlock );

    std::unique_ptr< engine::Scope > context( new engine::Scope( ) );
    mScopes.push( std::move( context ) );

    token.accept( * this );
    mValue.release( );

    llvm::verifyFunction( * function );

    return function;
}
