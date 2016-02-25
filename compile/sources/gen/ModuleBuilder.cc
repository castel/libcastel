#include <stdexcept>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/string.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/CodeBuilder.hh"
#include "castel/gen/ModuleBuilder.hh"
#include "castel/gen/Scope.hh"
#include "castel/runtime/Module.hh"

using namespace castel;
using gen::ModuleBuilder;

llvm::Module * ModuleBuilder::build( llvm::LLVMContext & context, llvm::Module * module ) const
{
    if ( ! mStatements )
        throw std::runtime_error( "ModuleBuilders must have a 'statements' field when built" );

    llvm::Function * mainFunction = llvm::Function::Create( gen::helper::type< runtime::Module::Signature >( context ), llvm::GlobalVariable::ExternalLinkage, mName, module );
    mainFunction->setPersonalityFn( module->getFunction( "Castel_personality" ) );

    llvm::BasicBlock * bootstrapBlock = llvm::BasicBlock::Create( context, "bootstrap" );
    llvm::BasicBlock * entryBlock = llvm::BasicBlock::Create( context, "entry" );

    mainFunction->getBasicBlockList( ).push_back( bootstrapBlock );
    mainFunction->getBasicBlockList( ).push_back( entryBlock );

    llvm::IRBuilder< > irBuilder( context );
    irBuilder.SetInsertPoint( bootstrapBlock );
    irBuilder.CreateBr( entryBlock );
    irBuilder.SetInsertPoint( entryBlock );

    llvm::Function::ArgumentListType::iterator runtimeArguments = mainFunction->getArgumentList( ).begin( );
    llvm::Value * runtimeArguments_runner = runtimeArguments ++;

    {{ gen::Scope scope( context, module, bootstrapBlock );

       for ( auto & globalName : mGlobals ) {
           llvm::Function * globalInitializer = llvm::Function::Create( castel::gen::helper::type< castel::runtime::Module::GlobalInitializerSignature >( context ), llvm::GlobalValue::ExternalLinkage, globalName + "_generator", module );
           scope.declare( irBuilder, globalName, gen::helper::call( context, module, irBuilder, globalInitializer, runtimeArguments_runner, gen::helper::string( irBuilder, globalName ) ) );
        }

       gen::CodeBuilder( )
           .statements( mStatements )
       .build( context, module, irBuilder, scope );

       llvm::BasicBlock * lastBlock = & ( mainFunction->getBasicBlockList( ).back( ) );
       if ( lastBlock->empty( ) || ! lastBlock->back( ).isTerminator( ) ) {
           irBuilder.SetInsertPoint( lastBlock, lastBlock->end( ) );
           irBuilder.CreateRet( gen::helper::call( context, module, irBuilder, "Castel_Undefined_create" ) );
       }
    }}

    return module;
}
