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
    llvm::Value * conditionValue = mBuilder.CreateFCmpONE( mValue.release( ), llvm::ConstantFP::get( mContext, llvm::APFloat( 0.0 ) ) );

    llvm::Function * function = mBuilder.GetInsertBlock( )->getParent( );

    if ( astIfStatement.elseBranch( ) ) {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
        llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mContext, "else" );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

        llvm::Value * final = mBuilder.CreateCondBr( conditionValue, thenBranch, elseBranch );

        mBuilder.SetInsertPoint( thenBranch );
        astIfStatement.thenBranch( )->accept( *this );
        if ( thenBranch->empty( ) || ! thenBranch->back( ).isTerminator( ) )
            mBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( elseBranch );

        mBuilder.SetInsertPoint( elseBranch );
        astIfStatement.elseBranch( )->accept( *this );
        if ( elseBranch->empty( ) || ! elseBranch->back( ).isTerminator( ) )
            mBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mBuilder.SetInsertPoint( finallyBranch );

    } else {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

        llvm::Value * final = mBuilder.CreateCondBr( conditionValue, thenBranch, finallyBranch );

        mBuilder.SetInsertPoint( thenBranch );
        astIfStatement.thenBranch( )->accept( *this );
        mBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mBuilder.SetInsertPoint( finallyBranch );

    }

    if ( astIfStatement.next( ) ) {
        astIfStatement.next( )->accept( *this );
    }

}
