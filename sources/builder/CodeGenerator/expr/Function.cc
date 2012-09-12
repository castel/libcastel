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
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/Closure.hh"
#include "castel/utils/Linked.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Function & astFunctionExpression )
{
    /* Checks that the AST has at least one statement */
    if ( ! astFunctionExpression.statements( ) )
        throw std::runtime_error( "Missing body" );

    /* Creates llvm function */
    llvm::Function * llvmFunction = mContext.declareGlobalFunction< runtime::Box * ( runtime::Box ***, unsigned int, runtime::Box ** ) >( "", llvm::Function::ExternalLinkage );

    /* Gets the current insert point (we will need it later) */
    llvm::BasicBlock * llvmCurrentBasicBlock = mContext.irBuilder( ).GetInsertBlock( );
    llvm::BasicBlock::iterator llvmCurrentPoint = mContext.irBuilder( ).GetInsertPoint( );

    /* Sets the IRBuilder insert point at the start of the newly created function */
    llvm::BasicBlock * llvmNewBasicBlock = llvm::BasicBlock::Create( mContext.llvmContext( ), "", llvmFunction );
    mContext.irBuilder( ).SetInsertPoint( llvmNewBasicBlock );

    /* Starts a new closure, using the parent environment */
    builder::Closure closure( mContext, * llvmFunction, ! mClosureStack.empty( ) ? mClosureStack.top( ) : nullptr );
    mClosureStack.push( & closure );

    /* Declares each parameter into the closure */
    unsigned int arity = 0;
    llvm::Value * deferredArgv = ++ ++ llvmFunction->getArgumentList( ).begin( );
    for ( auto & astFunctionParameter : astFunctionExpression.parameters( ) )
        closure.declare( astFunctionParameter.name( ), mContext.irBuilder( ).CreateLoad( mContext.irBuilder( ).CreateConstGEP1_32( deferredArgv, arity ++ ) ) );
    llvm::Value * deferredArgc = llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, arity ) );

    /* Constructs function body */
    astFunctionExpression.statements( )->accept( *this );

    /* If no value is returned, we return undefined */
    llvm::BasicBlock * llvmLastBasicBlock = mContext.irBuilder( ).GetInsertBlock( );
    if ( llvmLastBasicBlock->empty( ) || ! llvmLastBasicBlock->back( ).isTerminator( ) )
        mContext.irBuilder( ).CreateRet( mContext.irBuilder( ).CreateCastelCall( "castelUndefined_create" ) );

    /* Clotures the closure */
    mClosureStack.pop( );
    closure.finalize( );

    /* Restore insert point */
    mContext.irBuilder( ).SetInsertPoint( llvmCurrentBasicBlock, llvmCurrentPoint );

    /* Pseudo-returns a box containing this function, linked with the current function environment table */
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelFunction_create", mClosureStack.top( )->environmentTable( ), llvmFunction, deferredArgc ) );
}
