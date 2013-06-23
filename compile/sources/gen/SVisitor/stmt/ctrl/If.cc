#include <stdexcept>

#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Value.h>

#include "castel/ast/stmt/ctrl/If.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/ast/Statement.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::ctrl::If const & ifControlAst )
{
    ast::tools::Hold< ast::Expression > const & conditionAst = ifControlAst.condition( );
    ast::tools::Hold< ast::Statement > const & thenBranchAst = ifControlAst.thenBranch( );
    ast::tools::Hold< ast::Statement > const & elseBranchAst = ifControlAst.elseBranch( );

    if ( conditionAst )
        throw std::runtime_error( "'If' statements must have a condition when built" );

    if ( thenBranchAst )
        throw std::runtime_error( "'If' statements must have a 'then' branch when built" );

    llvm::Value * condition = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * conditionAst );
    llvm::Value * booleanCast = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Operator_boolCast", condition );
    llvm::Value * test = mIRBuilder.CreateICmpEQ( booleanCast, llvm::ConstantInt::getTrue( mContext ) );

    llvm::Function * function = mIRBuilder.GetInsertBlock( )->getParent( );

    if ( elseBranchAst != nullptr ) {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
        llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mContext, "else" );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

        mIRBuilder.CreateCondBr( test, thenBranch, elseBranch );

        mIRBuilder.SetInsertPoint( thenBranch );
        gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
            .run( * thenBranchAst );
        if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( elseBranch );

        mIRBuilder.SetInsertPoint( elseBranch );
        gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
            .run( * elseBranchAst );
        if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mIRBuilder.SetInsertPoint( finallyBranch );

    } else {

        llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
        llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

        mIRBuilder.CreateCondBr( test, thenBranch, finallyBranch );

        mIRBuilder.SetInsertPoint( thenBranch );
        gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
            .run( * thenBranchAst );
        if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
            mIRBuilder.CreateBr( finallyBranch );

        function->getBasicBlockList( ).push_back( finallyBranch );

        mIRBuilder.SetInsertPoint( finallyBranch );

    }

}
