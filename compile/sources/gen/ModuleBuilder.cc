#include <vector>

#include <llvm/IRBuilder.h>
#include <llvm/TypeBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/CodeBuilder.hh"
#include "castel/gen/ModuleBuilder.hh"
#include "castel/gen/Scope.hh"
#include "castel/runtime/Module.hh"

using namespace castel;
using gen::ModuleBuilder;

llvm::Module * ModuleBuilder::build( llvm::LLVMContext & context, llvm::Module * module ) const
{
    llvm::Function * mainFunction = llvm::Function::Create( gen::helper::type< runtime::Module::Signature >( context ), llvm::GlobalVariable::ExternalLinkage, "main", module );

    llvm::BasicBlock * bootstrapBlock = llvm::BasicBlock::Create( context, "bootstrap" );
    llvm::BasicBlock * entryBlock = llvm::BasicBlock::Create( context, "entry" );

    mainFunction->getBasicBlockList( ).push_back( bootstrapBlock );
    mainFunction->getBasicBlockList( ).push_back( entryBlock );

    llvm::IRBuilder< > irBuilder( context );
    irBuilder.SetInsertPoint( bootstrapBlock );
    irBuilder.CreateBr( entryBlock );
    irBuilder.SetInsertPoint( entryBlock );

    llvm::Function::ArgumentListType::iterator runtimeArguments = mainFunction->getArgumentList( ).begin( );
    llvm::Value * runtimeArguments_process = runtimeArguments ++;

    {{ gen::Scope scope( context, module, bootstrapBlock );
       scope.declare( irBuilder, "process", runtimeArguments_process );

       gen::CodeBuilder( )
           .statements( mStatements )
       .build( context, module, irBuilder, scope );

       llvm::BasicBlock * lastBlock = & ( mainFunction->getBasicBlockList( ).back( ) );
       if ( lastBlock->empty( ) || ! lastBlock->back( ).isTerminator( ) ) {
           irBuilder.SetInsertPoint( lastBlock, lastBlock->end( ) );
           irBuilder.CreateRet( gen::helper::call( context, module, irBuilder, "castelUndefined_create" ) );
       }
    }}

    return module;
}
