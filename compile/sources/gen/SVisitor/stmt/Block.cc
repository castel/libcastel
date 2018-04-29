#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>

#include "castel/ast/stmt/Block.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::Block const & blockStatementAst )
{
    llvm::BasicBlock * bootstrapBlock = llvm::BasicBlock::Create( mContext, "scope:bootstrap" );
    llvm::BasicBlock * scriptBlock = llvm::BasicBlock::Create( mContext, "scope:script" );

    llvm::BasicBlock * currentBlock = mIRBuilder.GetInsertBlock( );
    llvm::Function * currentFunction = currentBlock->getParent( );

    currentFunction->getBasicBlockList( ).push_back( bootstrapBlock );
    currentFunction->getBasicBlockList( ).push_back( scriptBlock );

    mIRBuilder.CreateBr( bootstrapBlock );
    mIRBuilder.SetInsertPoint( bootstrapBlock );
    mIRBuilder.CreateBr( scriptBlock );
    mIRBuilder.SetInsertPoint( scriptBlock );

    llvm::Function::arg_iterator runtimeArguments = currentFunction->arg_begin( );
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;

    {{ gen::Scope scope( mContext, mModule, bootstrapBlock, mScope, runtimeArguments_parentEnvironmentTable );

        for ( auto const & statement : blockStatementAst.statements( ) ) {
            gen::SVisitor( mContext, mModule, mIRBuilder, mScope ).run( * statement );
        }
    }}
}
