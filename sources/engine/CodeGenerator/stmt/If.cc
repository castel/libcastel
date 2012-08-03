#include <stdexcept>

#include <llvm/ADT/APFloat.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Value.h>

#include "p9/ast/stmt/If.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::stmt::If & astIfStatement )
{
    if ( ! astIfStatement.condition( ) )
        throw std::runtime_error( "Missing condition" );
    if ( ! astIfStatement.thenBranch( ) )
        throw std::runtime_error( "Missing then branch" );

    astIfStatement.condition( )->accept( *this );
    llvm::Value * testValue = mLLVMHelpers.boxToDouble( mValue.release( ) );
    llvm::Value * conditionValue = mGenerationEngine.irBuilder( ).CreateFCmpONE( testValue, llvm::ConstantFP::get( mGenerationEngine.llvmContext( ), llvm::APFloat( 0.0 ) ) );

    llvm::Function * function = mGenerationEngine.irBuilder( ).GetInsertBlock( )->getParent( );

    if ( astIfStatement.elseBranch( ) ) {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "then", function );
        llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "else" );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "finally" );

        llvm::Value * final = mGenerationEngine.irBuilder( ).CreateCondBr( conditionValue, thenBranch, elseBranch );

        mGenerationEngine.irBuilder( ).SetInsertPoint( thenBranch );
        astIfStatement.thenBranch( )->accept( *this );
        if ( thenBranch->empty( ) || ! thenBranch->back( ).isTerminator( ) )
            mGenerationEngine.irBuilder( ).CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( elseBranch );

        mGenerationEngine.irBuilder( ).SetInsertPoint( elseBranch );
        astIfStatement.elseBranch( )->accept( *this );
        if ( elseBranch->empty( ) || ! elseBranch->back( ).isTerminator( ) )
            mGenerationEngine.irBuilder( ).CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mGenerationEngine.irBuilder( ).SetInsertPoint( finallyBranch );

    } else {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "then", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mGenerationEngine.llvmContext( ), "finally" );

        llvm::Value * final = mGenerationEngine.irBuilder( ).CreateCondBr( conditionValue, thenBranch, finallyBranch );

        mGenerationEngine.irBuilder( ).SetInsertPoint( thenBranch );
        astIfStatement.thenBranch( )->accept( *this );
        if ( thenBranch->empty( ) || ! thenBranch->back( ).isTerminator( ) )
            mGenerationEngine.irBuilder( ).CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mGenerationEngine.irBuilder( ).SetInsertPoint( finallyBranch );

    }

    if ( astIfStatement.next( ) ) {
        astIfStatement.next( )->accept( *this );
    }

}
