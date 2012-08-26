#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <llvm/Analysis/Verifier.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

#include "castel/ast/expr/Function.hh"
#include "castel/engine/CodeGenerator.hh"
#include "castel/engine/Scope.hh"
#include "castel/utils/Linked.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::expr::Function & astFunctionExpression )
{
    /* Checks that the AST has at least one statement */
    if ( ! astFunctionExpression.statements( ) )
        throw std::runtime_error( "Missing body" );

    /* Crafts function type - engine::Box * (*)( engine::Box *** environment, engine::Box * arguments... ) */
    llvm::Type * returnType = mpllvm::get< engine::Box * >( mGenerationEngine.llvmContext( ) );

    std::vector< llvm::Type * > argumentsTypes;
    argumentsTypes.push_back( mpllvm::get< engine::Box *** >( mGenerationEngine.llvmContext( ) ) );
    argumentsTypes.insert( argumentsTypes.begin( ), std::distance( utils::begin( astFunctionExpression.parameters( ) ), utils::end( astFunctionExpression.parameters( ) ) ), mpllvm::get< engine::Box * >( mGenerationEngine.llvmContext( ) ) );

    llvm::FunctionType * functionType = llvm::FunctionType::get( returnType, argumentsTypes, false );

    /* Creates llvm function */
    llvm::Function * llvmFunction = llvm::Function::Create( functionType, llvm::Function::ExternalLinkage, "", & mGenerationEngine.module( ) );

    /* Gets the current insert point (we will need it later) */
    llvm::BasicBlock * currentBasicBlock = mGenerationEngine.irBuilder( ).GetInsertBlock( );
    llvm::BasicBlock::iterator currentPoint = mGenerationEngine.irBuilder( ).GetInsertPoint( );

    /* Sets the IRBuilder insert point at the start of the newly created function */
    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "", llvmFunction );
    mGenerationEngine.irBuilder( ).SetInsertPoint( basicBlock );

    /* Starts a new closure, using the parent environment */
    engine::Closure closure( mGenerationEngine, * llvmFunction, ! mClosureStack.empty( ) ? mClosureStack.top( ) : nullptr );
    mClosureStack.push( & closure );

    /* Declares each parameter into the closure */
    auto llvmArgIterator = llvmFunction->arg_begin( );
    llvm::Value * environment = llvmArgIterator ++;
    for ( auto & parameter : astFunctionExpression.parameters( ) )
        closure.declare( parameter.name( ), llvmArgIterator ++ );

    /* Constructs function body */
    astFunctionExpression.statements( )->accept( *this );

    /* Clotures the closure */
    mClosureStack.pop( );
    closure.finalize( );

    /* Restore insert point */
    mGenerationEngine.irBuilder( ).SetInsertPoint( currentBasicBlock, currentPoint );

    /* Checks function integrity */
    //llvmFunction->dump( );
    //llvm::verifyFunction( * llvmFunction );

    /* Pseudo-returns a box containing this function, linked with the current function environment table */
    mValue.reset( mLLVMHelpers.functionToBox( llvmFunction, mClosureStack.top( )->environmentTable( ) ) );
}
