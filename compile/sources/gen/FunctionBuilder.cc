#include <vector>

#include <llvm/IRBuilder.h>
#include <llvm/TypeBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/tools/Linked.hh"
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
    llvm::Function * function = llvm::Function::Create( gen::helper::type< runtime::boxes::Function::Signature >( context ), llvm::GlobalVariable::ExternalLinkage, mName, module );
    llvm::Value * argumentCount = gen::helper::i32( context, std::distance( ast::tools::begin( mParameters ), ast::tools::end( mParameters ) ) + ( mUseThis ? 1 : 0 ) );
    llvm::Value * functionBox = gen::helper::call( context, module, parentIRBuilder, "castelFunction_create", function, argumentCount, parentScope.environmentTable( ) );

    llvm::BasicBlock * bootstrapBlock = llvm::BasicBlock::Create( context, "bootstrap" );
    llvm::BasicBlock * entryBlock = llvm::BasicBlock::Create( context, "entry" );

    function->getBasicBlockList( ).push_back( bootstrapBlock );
    function->getBasicBlockList( ).push_back( entryBlock );

    llvm::IRBuilder< > irBuilder( context );
    irBuilder.SetInsertPoint( bootstrapBlock );
    irBuilder.CreateBr( entryBlock );
    irBuilder.SetInsertPoint( entryBlock );

    llvm::Function::ArgumentListType::iterator runtimeArguments = function->getArgumentList( ).begin( );
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;
    llvm::Value * runtimeArguments_argumentCount = runtimeArguments ++;
    llvm::Value * runtimeArguments_argumentArray = runtimeArguments ++;

    {{ gen::Scope scope( context, module, bootstrapBlock, parentScope, runtimeArguments_parentEnvironmentTable );

       unsigned int parameterIndex = 0;

       if ( mUseThis )
           scope.declare( irBuilder, "this", irBuilder.CreateLoad( irBuilder.CreateConstGEP1_32( runtimeArguments_argumentArray, parameterIndex ++ ) ) );

       for ( auto & parameter : mParameters )
           scope.declare( irBuilder, parameter.name( ), irBuilder.CreateLoad( irBuilder.CreateConstGEP1_32( runtimeArguments_argumentArray, parameterIndex ++ ) ) );

       gen::CodeBuilder( )
           .statements( mStatements )
       .build( context, module, irBuilder, scope );

       llvm::BasicBlock * lastBlock = & ( function->getBasicBlockList( ).back( ) );
       if ( lastBlock->empty( ) || ! lastBlock->back( ).isTerminator( ) ) {
           irBuilder.SetInsertPoint( lastBlock, lastBlock->end( ) );
           irBuilder.CreateRet( gen::helper::call( context, module, irBuilder, "castelUndefined_create" ) );
       }
    }}

    return functionBox;
}
