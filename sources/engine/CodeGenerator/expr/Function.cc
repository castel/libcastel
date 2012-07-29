#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <llvm/Analysis/Verifier.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

#include "p9/ast/expr/Function.hh"
#include "p9/engine/CodeGenerator.hh"
#include "p9/engine/Scope.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Function & function )
{
    if ( ! function.statements( ) )
        throw std::runtime_error( "Missing body" );

    llvm::FunctionType * functionType = llvm::FunctionType::get( llvm::PointerType::get( mGenerationEngine.boxType( ), 0 ), { }, false );
    llvm::Function * llvmFunction = llvm::Function::Create( functionType, llvm::Function::ExternalLinkage, "", &mGenerationEngine.module( ) );

    std::unique_ptr< engine::Scope > context( new engine::Scope( ) );
    mScopes.push( std::move( context ) );

    llvm::BasicBlock * currentBasicBlock = mGenerationEngine.builder( ).GetInsertBlock( );
    llvm::BasicBlock::iterator currentPoint = mGenerationEngine.builder( ).GetInsertPoint( );

    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create( mGenerationEngine.context( ), "", llvmFunction );
    mGenerationEngine.builder( ).SetInsertPoint( basicBlock );

    function.statements( )->accept( *this );
    mValue.release( );

    mGenerationEngine.builder( ).SetInsertPoint( currentBasicBlock, currentPoint );
    mScopes.pop( );

    llvm::verifyFunction( * llvmFunction );

    mValue.reset( mLLVMHelpers.functionToBox( llvmFunction ) );
}
