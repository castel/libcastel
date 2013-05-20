#include <stdexcept>
#include <vector>

#include <llvm/Transforms/Utils/BasicBlockUtils.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/Value.h>

#include "castel/ast/stmt/ctrl/Try.hh"
#include "castel/ast/Statement.hh"
#include "castel/gen/CodeBuilder.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

static std::vector< llvm::Value * > fetchArguments( llvm::CallInst * callInstruction )
{
    unsigned argc = callInstruction->getNumArgOperands( );
    std::vector< llvm::Value * > argv;

    for ( unsigned t = 0; t < argc; ++ t )
        argv.push_back( callInstruction->getArgOperand( t ) );

    return argv;
}

void SVisitor::visit( ast::stmt::ctrl::Try & tryControlAst )
{
    ast::Statement * tryBranchAst = tryControlAst.tryBranch( );
    ast::Statement * elseBranchAst = tryControlAst.elseBranch( );

    if ( tryBranchAst == nullptr )
        throw std::runtime_error( "Missing 'try' branch" );

    if ( elseBranchAst == nullptr )
        throw std::runtime_error( "Missing 'else' branch" );

    llvm::Function * function = mIRBuilder.GetInsertBlock( )->getParent( );

    llvm::BasicBlock * tryBranch = llvm::BasicBlock::Create( mContext, "try" );
    llvm::BasicBlock * catchBranch = llvm::BasicBlock::Create( mContext, "catch" );
    llvm::BasicBlock * continueBranch = llvm::BasicBlock::Create( mContext, "continue" );

    mIRBuilder.CreateBr( tryBranch );

    function->getBasicBlockList( ).push_back( tryBranch );

    mIRBuilder.SetInsertPoint( tryBranch );
    gen::CodeBuilder( ).statements( tryBranchAst )
        .build( mContext, mModule, mIRBuilder, mScope );
    if ( tryBranch->empty( ) || ! tryBranch->back( ).isTerminator( ) )
        mIRBuilder.CreateBr( continueBranch );

    for ( llvm::Function::iterator basicBlock = tryBranch; basicBlock != function->end( ); ++ basicBlock ) {
        for ( llvm::BasicBlock::iterator instruction = basicBlock->begin( ); instruction != basicBlock->end( ); ++ instruction ) {

            llvm::CallInst * callInstruction = dynamic_cast< llvm::CallInst * >( instruction.getNodePtrUnchecked( ) );

            if ( callInstruction == nullptr )
                continue ;

            llvm::BasicBlock::iterator nextInstruction = callInstruction;
            ++ nextInstruction;

            tryBranch = basicBlock->splitBasicBlock( nextInstruction, "next" );

            llvm::BasicBlock::iterator extraneousBranchInstruction = callInstruction;
            ++ extraneousBranchInstruction;
            extraneousBranchInstruction->eraseFromParent( );

            llvm::Value * callee = callInstruction->getCalledValue( );
            std::vector< llvm::Value * > arguments = fetchArguments( callInstruction );

            llvm::InvokeInst * invokeInstruction = llvm::InvokeInst::Create( callee, tryBranch, catchBranch, arguments );
            llvm::ReplaceInstWithInst( basicBlock->getInstList( ), instruction, invokeInstruction );

            instruction = invokeInstruction;

        }
    }

    function->getBasicBlockList( ).push_back( catchBranch );

    mIRBuilder.SetInsertPoint( catchBranch );
    if ( catchBranch->empty( ) || ! catchBranch->back( ).isTerminator( ) )
        mIRBuilder.CreateBr( continueBranch );

    function->getBasicBlockList( ).push_back( continueBranch );

    mIRBuilder.SetInsertPoint( continueBranch );

}
