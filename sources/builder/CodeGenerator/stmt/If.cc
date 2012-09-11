#include <stdexcept>

#include <llvm/ADT/APFloat.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Value.h>

#include "castel/ast/stmt/If.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::If & astIfStatement )
{
    if ( ! astIfStatement.condition( ) )
        throw std::runtime_error( "Missing condition" );
    if ( ! astIfStatement.thenBranch( ) )
        throw std::runtime_error( "Missing then branch" );

    astIfStatement.condition( )->accept( * this );
    llvm::Value * testValue = /*todo*/llvm::ConstantFP::get( mContext.llvmContext( ), llvm::APFloat( 0.0 ) );
    llvm::Value * conditionValue = mContext.irBuilder( ).CreateFCmpONE( testValue, llvm::ConstantFP::get( mContext.llvmContext( ), llvm::APFloat( 0.0 ) ) );

    llvm::Function * llvmFunction = mContext.irBuilder( ).GetInsertBlock( )->getParent( );

    if ( astIfStatement.elseBranch( ) ) {

        llvm::BasicBlock * llvmThenBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "then", llvmFunction );
        llvm::BasicBlock * llvmElseBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "else" );
        llvm::BasicBlock * llvmFinallyBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "finally" );

        mContext.irBuilder( ).CreateCondBr( conditionValue, llvmThenBranch, llvmElseBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmThenBranch );
        astIfStatement.thenBranch( )->accept( * this );
        if ( llvmThenBranch->empty( ) || ! llvmThenBranch->back( ).isTerminator( ) )
            mContext.irBuilder( ).CreateBr( llvmFinallyBranch );

        llvmFunction->getBasicBlockList( ).push_back( llvmElseBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmElseBranch );
        astIfStatement.elseBranch( )->accept( * this );
        if ( llvmElseBranch->empty( ) || ! llvmElseBranch->back( ).isTerminator( ) )
            mContext.irBuilder( ).CreateBr( llvmFinallyBranch );

        llvmFunction->getBasicBlockList( ).push_back( llvmFinallyBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmFinallyBranch );

    } else {

        llvm::BasicBlock * llvmThenBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "then", llvmFunction );
        llvm::BasicBlock * llvmFinallyBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "finally" );

        mContext.irBuilder( ).CreateCondBr( conditionValue, llvmThenBranch, llvmFinallyBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmThenBranch );
        astIfStatement.thenBranch( )->accept( * this );
        if ( llvmThenBranch->empty( ) || ! llvmThenBranch->back( ).isTerminator( ) )
            mContext.irBuilder( ).CreateBr( llvmFinallyBranch );

        llvmFunction->getBasicBlockList( ).push_back( llvmFinallyBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmFinallyBranch );

    }

    if ( astIfStatement.next( ) ) {
        astIfStatement.next( )->accept( * this );
    }

}
