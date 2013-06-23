#include <stdexcept>
#include <vector>

#include <llvm/Transforms/Utils/BasicBlockUtils.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/Value.h>

#include "castel/ast/stmt/ctrl/Try.hh"
#include "castel/ast/Statement.hh"
#include "castel/gen/helper/null.hh"
#include "castel/gen/helper/type.hh"
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

void SVisitor::visit( ast::stmt::ctrl::Try const & tryControlAst )
{
    ast::tools::Hold< ast::Statement > const & tryBranchAst = tryControlAst.tryBranch( );
    ast::tools::Hold< ast::Statement > const & elseBranchAst = tryControlAst.elseBranch( );

    if ( tryBranchAst )
        throw std::runtime_error( "'Try/Catch' statements must have a 'try' branch when built" );

    if ( elseBranchAst )
        throw std::runtime_error( "'Try/Catch' statements must have a 'catch' branch when built" );

    llvm::Function * function = mIRBuilder.GetInsertBlock( )->getParent( );

    llvm::BasicBlock * tryBranch = llvm::BasicBlock::Create( mContext, "try" );
    llvm::BasicBlock * catchBranch = llvm::BasicBlock::Create( mContext, "catch" );
    llvm::BasicBlock * continueBranch = llvm::BasicBlock::Create( mContext, "continue" );

    mIRBuilder.CreateBr( tryBranch );

    function->getBasicBlockList( ).push_back( tryBranch );
    mIRBuilder.SetInsertPoint( tryBranch );

    gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
        .run( * tryBranchAst );
    if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
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

    llvm::Type * exceptionType = llvm::StructType::get( gen::helper::type< std::int8_t >( mContext ), gen::helper::type< std::int32_t >( mContext ), nullptr );
    llvm::Function * personality = mModule->getFunction( "Castel_personality" );
    llvm::LandingPadInst * landingPad = mIRBuilder.CreateLandingPad( exceptionType, personality, 0, "landingPad" );

    landingPad->addClause( gen::helper::null( gen::helper::type< void * >( mContext ) ) );

    gen::SVisitor( mContext, mModule, mIRBuilder, mScope )
        .run( * elseBranchAst );
    if ( mIRBuilder.GetInsertBlock( )->empty( ) || ! mIRBuilder.GetInsertBlock( )->back( ).isTerminator( ) )
        mIRBuilder.CreateBr( continueBranch );

    function->getBasicBlockList( ).push_back( continueBranch );
    mIRBuilder.SetInsertPoint( continueBranch );

}
