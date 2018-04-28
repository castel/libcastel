#include <stdexcept>
#include <vector>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/i32.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/CodeBuilder.hh"
#include "castel/gen/FunctionBuilder.hh"
#include "castel/gen/Scope.hh"
#include "castel/runtime/boxes/Function.hh"

using namespace castel;
using gen::FunctionBuilder;

llvm::Value * FunctionBuilder::build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & parentIRBuilder, gen::Scope & parentScope )
{
    if ( ! mParameters )
        throw std::runtime_error( "FunctionBuilders must have a 'parameters' field when built" );

    if ( ! mStatements )
        throw std::runtime_error( "FunctionBuilders must have a 'statements' field when built" );

    llvm::Function * function = llvm::Function::Create( gen::helper::type< runtime::boxes::Function::Signature >( context ), llvm::GlobalVariable::PrivateLinkage, mName, module );
    function->setPersonalityFn( module->getFunction( "Castel_personality" ) );

    llvm::Value * argumentCount = gen::helper::i32( context, mParameters->size( ) + ( mUseThis ? 1 : 0 ) );
    llvm::Value * functionBox = gen::helper::call( context, module, parentIRBuilder, "Castel_Function_create", function, argumentCount, parentScope.environmentTable( ) );

    llvm::BasicBlock * bootstrapBlock = llvm::BasicBlock::Create( context, "bootstrap" );
    llvm::BasicBlock * entryBlock = llvm::BasicBlock::Create( context, "entry" );

    function->getBasicBlockList( ).push_back( bootstrapBlock );
    function->getBasicBlockList( ).push_back( entryBlock );

    llvm::IRBuilder< > irBuilder( context );
    irBuilder.SetInsertPoint( bootstrapBlock );
    irBuilder.CreateBr( entryBlock );
    irBuilder.SetInsertPoint( entryBlock );

    llvm::Function::arg_iterator runtimeArguments = function->arg_begin( );
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;
    llvm::Value * runtimeArguments_argumentCount = runtimeArguments ++;
    llvm::Value * runtimeArguments_argumentArray = runtimeArguments ++;

    {{ gen::Scope scope( context, module, bootstrapBlock, parentScope, runtimeArguments_parentEnvironmentTable );

       unsigned int parameterIndex = 0;

       if ( mUseThis )
           scope.declare( irBuilder, "this", irBuilder.CreateLoad( irBuilder.CreateConstGEP1_32( runtimeArguments_argumentArray, parameterIndex ++ ) ) );

       for ( auto const & parameter : * mParameters )
           scope.declare( irBuilder, parameter->name( ), irBuilder.CreateLoad( irBuilder.CreateConstGEP1_32( runtimeArguments_argumentArray, parameterIndex ++ ) ) );

       gen::CodeBuilder( )
           .statements( mStatements )
       .build( context, module, irBuilder, scope );

       llvm::BasicBlock * lastBlock = & ( function->getBasicBlockList( ).back( ) );
       if ( lastBlock->empty( ) || ! lastBlock->back( ).isTerminator( ) ) {
           irBuilder.SetInsertPoint( lastBlock, lastBlock->end( ) );
           irBuilder.CreateRet( gen::helper::call( context, module, irBuilder, "Castel_Undefined_create" ) );
       }
    }}

    return functionBox;
}
