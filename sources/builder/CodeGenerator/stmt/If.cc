#include <stdexcept>

#include <llvm/ADT/APFloat.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Value.h>

#include "castel/ast/stmt/If.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::If & astIfStatement )
{
    ast::Expression * astCondition = astIfStatement.condition( );
    ast::Statement * astThenBranch = astIfStatement.thenBranch( );
    ast::Statement * astElseBranch = astIfStatement.elseBranch( );

    if ( astCondition == nullptr )
        throw std::runtime_error( "Missing condition" );

    if ( astThenBranch == nullptr )
        throw std::runtime_error( "Missing then branch" );

    llvm::Value * testValue = mContext.irBuilder( ).CreateCastelCall( "castel_operatorBool", builder::GetterGenerator( mScope ).run( * astCondition ) );
    llvm::Value * conditionValue = mContext.irBuilder( ).CreateICmpEQ( testValue, llvm::ConstantInt::getTrue( mContext.llvmContext( ) ) );

    llvm::Function * llvmFunction = mContext.irBuilder( ).GetInsertBlock( )->getParent( );

    if ( astElseBranch != nullptr ) {

        llvm::BasicBlock * llvmThenBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "then", llvmFunction );
        llvm::BasicBlock * llvmElseBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "else" );
        llvm::BasicBlock * llvmFinallyBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "finally" );

        mContext.irBuilder( ).CreateCondBr( conditionValue, llvmThenBranch, llvmElseBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmThenBranch );
        builder::CodeGenerator( mScope ).run( * astThenBranch );
        if ( llvmThenBranch->empty( ) || ! llvmThenBranch->back( ).isTerminator( ) )
            mContext.irBuilder( ).CreateBr( llvmFinallyBranch );

        llvmFunction->getBasicBlockList( ).push_back( llvmElseBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmElseBranch );
        builder::CodeGenerator( mScope ).run( * astElseBranch );
        if ( llvmElseBranch->empty( ) || ! llvmElseBranch->back( ).isTerminator( ) )
            mContext.irBuilder( ).CreateBr( llvmFinallyBranch );

        llvmFunction->getBasicBlockList( ).push_back( llvmFinallyBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmFinallyBranch );

    } else {

        llvm::BasicBlock * llvmThenBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "then", llvmFunction );
        llvm::BasicBlock * llvmFinallyBranch = llvm::BasicBlock::Create( mContext.llvmContext( ), "finally" );

        mContext.irBuilder( ).CreateCondBr( conditionValue, llvmThenBranch, llvmFinallyBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmThenBranch );
        builder::CodeGenerator( mScope ).run( * astThenBranch );
        if ( llvmThenBranch->empty( ) || ! llvmThenBranch->back( ).isTerminator( ) )
            mContext.irBuilder( ).CreateBr( llvmFinallyBranch );

        llvmFunction->getBasicBlockList( ).push_back( llvmFinallyBranch );

        mContext.irBuilder( ).SetInsertPoint( llvmFinallyBranch );

    }

}
