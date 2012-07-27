#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <llvm/Analysis/Verifier.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Type.h>

#include "p9/ast/expr/Function.hh"
#include "p9/engine/CodeGenerator.hh"
#include "p9/engine/Scope.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Function & function )
{
    if ( ! function.statements( ) )
        throw std::runtime_error( "Missing body" );

    llvm::Type * doubleType = llvm::Type::getDoubleTy( mGenerationEngine.context( ) );

    llvm::Type * returnType = doubleType;
    std::vector< llvm::Type * > parametersTypes;

    llvm::FunctionType * functionType = llvm::FunctionType::get( returnType, parametersTypes, false );
    llvm::Function * llvmFunction = llvm::Function::Create( functionType, llvm::Function::ExternalLinkage, "", &mGenerationEngine.module( ) );

    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create( mGenerationEngine.context( ), "", llvmFunction );
    mGenerationEngine.builder( ).SetInsertPoint( basicBlock );

    std::unique_ptr< engine::Scope > context( new engine::Scope( ) );
    mScopes.push( std::move( context ) );

    function.statements( )->accept( *this );
    mValue.release( );

    llvm::verifyFunction( * llvmFunction );
    mValue.reset( llvmFunction );
}
