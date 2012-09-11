#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/TypeBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>
#include <llvm/Value.h>

#include "castel/ast/Statement.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using builder::CodeGenerator;

llvm::Function * CodeGenerator::codegen( ast::Statement & astStatement )
{
    llvm::Function * llvmFunction = mContext.declareGlobalFunction< runtime::Box * ( runtime::Box *** ) >( "main", llvm::Function::ExternalLinkage );

    llvm::BasicBlock * llvmBasicBlock = llvm::BasicBlock::Create( mContext.llvmContext( ), "", llvmFunction );
    mContext.irBuilder( ).SetInsertPoint( llvmBasicBlock );

    builder::Closure closure( mContext, * llvmFunction );
    mClosureStack.push( & closure );

    astStatement.accept( * this );
    mValue.release( );

    mClosureStack.pop( );
    closure.finalize( );

    llvm::verifyModule( mContext.llvmModule( ) );

    return llvmFunction;
}
