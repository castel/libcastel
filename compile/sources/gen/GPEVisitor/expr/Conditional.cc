#include <stdexcept>

#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Conditional.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using castel::gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::Conditional const & conditionalAst )
{
    ast::tools::Hold< ast::Expression > const & conditionAst = conditionalAst.condition( );
    ast::tools::Hold< ast::Expression > const & thenExpressionAst = conditionalAst.thenExpression( );
    ast::tools::Hold< ast::Expression > const & elseExpressionAst = conditionalAst.elseExpression( );

    if ( ! conditionAst )
        throw std::runtime_error( "Conditional expressions must have a condition when built" );

    if ( ! thenExpressionAst )
        throw std::runtime_error( "Conditional expressions must have a 'then' expression when built" );

    if ( ! elseExpressionAst )
        throw std::runtime_error( "Conditional expressions must have an 'else' expression when built" );

    llvm::Value * condition = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * conditionAst );
    llvm::Value * booleanCast = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Operator_boolCast", condition );
    llvm::Value * test = mIRBuilder.CreateICmpEQ( booleanCast, llvm::ConstantInt::getTrue( mContext ) );

    llvm::Function * function = mIRBuilder.GetInsertBlock( )->getParent( );

    llvm::BasicBlock * thenBranch = llvm::BasicBlock::Create( mContext, "then", function );
    llvm::BasicBlock * elseBranch = llvm::BasicBlock::Create( mContext, "else" );
    llvm::BasicBlock * finallyBranch = llvm::BasicBlock::Create( mContext, "finally" );

    mIRBuilder.CreateCondBr( test, thenBranch, elseBranch );

    mIRBuilder.SetInsertPoint( thenBranch );
    llvm::Value * thenValue = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * thenExpressionAst );
    mIRBuilder.CreateBr( finallyBranch );
    thenBranch = mIRBuilder.GetInsertBlock( );

    function->getBasicBlockList( ).push_back( elseBranch );

    mIRBuilder.SetInsertPoint( elseBranch );
    llvm::Value * elseValue = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * elseExpressionAst );
    mIRBuilder.CreateBr( finallyBranch );
    elseBranch = mIRBuilder.GetInsertBlock( );

    function->getBasicBlockList( ).push_back( finallyBranch );

    mIRBuilder.SetInsertPoint( finallyBranch );

    llvm::PHINode * phiNode = mIRBuilder.CreatePHI( gen::helper::type< runtime::Box * >( mContext ), 2, "conditional" );
    phiNode->addIncoming( thenValue, thenBranch );
    phiNode->addIncoming( elseValue, elseBranch );

    mLastReturnedValue = phiNode;

}
