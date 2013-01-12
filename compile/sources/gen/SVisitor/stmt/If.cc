#include <stdexcept>

#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Value.h>

#include "castel/ast/stmt/If.hh"
#include "castel/ast/Expression.hh"
#include "castel/ast/Statement.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/CodeBuilder.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::If & ifStatementAst )
{
    ast::Expression * conditionAst = ifStatementAst.condition( );
    ast::Statement * thenBranchAst = ifStatementAst.thenBranch( );
    ast::Statement * elseBranchAst = ifStatementAst.elseBranch( );

    if ( conditionAst == nullptr )
        throw std::runtime_error( "Missing condition" );

    if ( thenBranchAst == nullptr )
        throw std::runtime_error( "Missing 'then' branch" );

    llvm::Value * condition = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * conditionAst );
    llvm::Value * booleanCast = gen::helper::call( mContext, mModule, mIRBuilder, "castel_operatorBool", condition );
    llvm::Value * test = mIRBuilder.CreateICmpEQ( booleanCast, llvm::ConstantInt::getTrue( mContext ) );

    llvm::Function * function = mIRBuilder.GetInsertBlock( )->getParent( );

    if ( elseBranchAst != nullptr ) {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
        llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mContext, "else" );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

        mIRBuilder.CreateCondBr( test, thenBranch, elseBranch );

        mIRBuilder.SetInsertPoint( thenBranch );
        gen::CodeBuilder( ).statements( thenBranchAst )
            .build( mContext, mModule, mIRBuilder, mScope );
        if ( thenBranch->empty( ) || ! thenBranch->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( elseBranch );

        mIRBuilder.SetInsertPoint( elseBranch );
        gen::CodeBuilder( ).statements( elseBranchAst )
            .build( mContext, mModule, mIRBuilder, mScope );
        if ( elseBranch->empty( ) || ! elseBranch->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mIRBuilder.SetInsertPoint( finallyBranch );

    } else {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

        mIRBuilder.CreateCondBr( test, thenBranch, finallyBranch );

        mIRBuilder.SetInsertPoint( thenBranch );
        gen::CodeBuilder( ).statements( thenBranchAst )
            .build( mContext, mModule, mIRBuilder, mScope );
        if ( thenBranch->empty( ) || ! thenBranch->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mIRBuilder.SetInsertPoint( finallyBranch );

    }

}
