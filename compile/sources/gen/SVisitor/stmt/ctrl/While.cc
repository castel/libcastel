#include <stdexcept>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>

#include "castel/ast/stmt/ctrl/While.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/ast/Statement.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::ctrl::While const & whileControlAst )
{
    ast::tools::Hold< ast::Expression > const & conditionAst = whileControlAst.condition( );
    ast::tools::Hold< ast::Statement > const & thenBranchAst = whileControlAst.thenBranch( );
    ast::tools::Hold< ast::Statement > const & elseBranchAst = whileControlAst.elseBranch( );

    if ( ! conditionAst )
        throw std::runtime_error( "'While' statements must have a condition when built" );

    if ( ! thenBranchAst )
        throw std::runtime_error( "'While' statements must have a 'then' branch when built" );

    llvm::Function * function = mIRBuilder.GetInsertBlock( )->getParent( );

    if ( elseBranchAst != nullptr ) {

        llvm::BasicBlock * initialBranch = llvm::BasicBlock::Create( mContext, "while:initial", function );
        llvm::BasicBlock * checkBranch = llvm::BasicBlock::Create( mContext, "while:check", function );
        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "while:then", function );
        llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mContext, "while:else", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "while:finally", function );

        mIRBuilder.CreateBr( initialBranch );

        mIRBuilder.SetInsertPoint( initialBranch );
        llvm::Value * initial_condition = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * conditionAst );
        llvm::Value * initial_booleanCast = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Operator_boolCast", initial_condition );
        llvm::Value * initial_test = mIRBuilder.CreateICmpEQ( initial_booleanCast, llvm::ConstantInt::getTrue( mContext ) );
        mIRBuilder.CreateCondBr( initial_test, thenBranch, elseBranch );

        mIRBuilder.SetInsertPoint( checkBranch );
        llvm::Value * check_condition = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * conditionAst );
        llvm::Value * check_booleanCast = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Operator_boolCast", check_condition );
        llvm::Value * check_test = mIRBuilder.CreateICmpEQ( check_booleanCast, llvm::ConstantInt::getTrue( mContext ) );
        mIRBuilder.CreateCondBr( check_test, thenBranch, finallyBranch );

        mIRBuilder.SetInsertPoint( thenBranch );
        gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
            .run( * thenBranchAst );
        if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( checkBranch );

        mIRBuilder.SetInsertPoint( elseBranch );
        gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
            .run( * elseBranchAst );
        if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        mIRBuilder.SetInsertPoint( finallyBranch );

    } else {

        llvm::BasicBlock * checkBranch = llvm::BasicBlock::Create( mContext, "while:check", function );
        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "while:then", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "while:finally", function );

        mIRBuilder.CreateBr( checkBranch );

        mIRBuilder.SetInsertPoint( checkBranch );
        llvm::Value * check_condition = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * conditionAst );
        llvm::Value * check_booleanCast = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Operator_boolCast", check_condition );
        llvm::Value * check_test = mIRBuilder.CreateICmpEQ( check_booleanCast, llvm::ConstantInt::getTrue( mContext ) );
        mIRBuilder.CreateCondBr( check_test, thenBranch, finallyBranch );

        mIRBuilder.SetInsertPoint( thenBranch );
        gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
            .run( * thenBranchAst );
        if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( checkBranch );

        mIRBuilder.SetInsertPoint( finallyBranch );

    }
}
