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
    llvm::Value * conditionValue = mGenerationEngine.builder( ).CreateFCmpONE( mValue.release( ), llvm::ConstantFP::get( mGenerationEngine.context( ), llvm::APFloat( 0.0 ) ) );

    llvm::Function * function = mGenerationEngine.builder( ).GetInsertBlock( )->getParent( );

    if ( astIfStatement.elseBranch( ) ) {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "then", function );
        llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "else" );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "finally" );

        llvm::Value * final = mGenerationEngine.builder( ).CreateCondBr( conditionValue, thenBranch, elseBranch );

        mGenerationEngine.builder( ).SetInsertPoint( thenBranch );
        astIfStatement.thenBranch( )->accept( *this );
        if ( thenBranch->empty( ) || ! thenBranch->back( ).isTerminator( ) )
            mGenerationEngine.builder( ).CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( elseBranch );

        mGenerationEngine.builder( ).SetInsertPoint( elseBranch );
        astIfStatement.elseBranch( )->accept( *this );
        if ( elseBranch->empty( ) || ! elseBranch->back( ).isTerminator( ) )
            mGenerationEngine.builder( ).CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mGenerationEngine.builder( ).SetInsertPoint( finallyBranch );

    } else {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "then", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mGenerationEngine.context( ), "finally" );

        llvm::Value * final = mGenerationEngine.builder( ).CreateCondBr( conditionValue, thenBranch, finallyBranch );

        mGenerationEngine.builder( ).SetInsertPoint( thenBranch );
        astIfStatement.thenBranch( )->accept( *this );
        mGenerationEngine.builder( ).CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mGenerationEngine.builder( ).SetInsertPoint( finallyBranch );

    }

    if ( astIfStatement.next( ) ) {
        astIfStatement.next( )->accept( *this );
    }

}
