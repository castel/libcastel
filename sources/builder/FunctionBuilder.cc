#include <llvm/ADT/APInt.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Value.h>

#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/FunctionBuilder.hh"

using namespace castel;
using builder::FunctionBuilder;

llvm::Value * FunctionBuilder::create( builder::Context & context, builder::Scope * parentScope ) const
{
    llvm::BasicBlock * llvmCurrentBasicBlock = context.irBuilder( ).GetInsertBlock( );
    llvm::BasicBlock::iterator llvmCurrentPoint = context.irBuilder( ).GetInsertPoint( );

    llvm::Function * llvmFunction = context.declareGlobalFunction< runtime::boxes::Function::Signature >( mName, llvm::Function::ExternalLinkage );
    llvm::Value * llvmArgumentCount = llvm::ConstantInt::get( context.llvmContext( ), llvm::APInt( 32, std::distance( utils::begin( mParameters ), utils::end( mParameters ) ) + ( mUseThis ? 1 : 0 ) ) );
    llvm::Value * llvmFunctionBox = context.irBuilder( ).CreateCastelCall( "castelFunction_create", llvmFunction, llvmArgumentCount, parentScope ? parentScope->environmentTable( ) : llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box ***, false >::get( context.llvmContext( ) ) ) );

    llvm::BasicBlock * llvmBootstrapBlock = llvm::BasicBlock::Create( context.llvmContext( ), "bootstrap" );
    llvm::BasicBlock * llvmStatementsBlock = llvm::BasicBlock::Create( context.llvmContext( ), "statements" );

    llvmFunction->getBasicBlockList( ).push_back( llvmBootstrapBlock );
    llvmFunction->getBasicBlockList( ).push_back( llvmStatementsBlock );

    context.irBuilder( ).SetInsertPoint( llvmBootstrapBlock );
    context.irBuilder( ).CreateBr( llvmStatementsBlock );
    context.irBuilder( ).SetInsertPoint( llvmStatementsBlock );

    llvm::Function::ArgumentListType::iterator runtimeArguments = llvmFunction->getArgumentList( ).begin( );
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;
    llvm::Value * runtimeArguments_argumentCount = runtimeArguments ++;
    llvm::Value * runtimeArguments_argumentsArray = runtimeArguments ++;

    //  We enclose the scope inside a C++ scope in order to explicitely destroy the scope when it is not needed anymore
    //  That's not required, but I think it improves readability.
    {{  builder::Scope scope( context, * llvmBootstrapBlock, parentScope );
        scope.parentEnvironmentTable( runtimeArguments_parentEnvironmentTable );

        unsigned int parameterCount = 0;
        if ( mUseThis )
            scope.declare( "this", context.irBuilder( ).CreateLoad( context.irBuilder( ).CreateConstGEP1_32( runtimeArguments_argumentsArray, parameterCount ++ ) ) );
        for ( auto & astParameter : mParameters )
            scope.declare( astParameter.name( ), context.irBuilder( ).CreateLoad( context.irBuilder( ).CreateConstGEP1_32( runtimeArguments_argumentsArray, parameterCount ++ ) ) );

        builder::CodeGenerator( scope ).run( * mStatements );

        llvm::BasicBlock * llvmLastBasicBlock = & llvmFunction->getBasicBlockList( ).back( );
        if ( llvmLastBasicBlock->empty( ) || ! llvmLastBasicBlock->back( ).isTerminator( ) ) {
            context.irBuilder( ).SetInsertPoint( llvmLastBasicBlock, llvmLastBasicBlock->end( ) );
            context.irBuilder( ).CreateRet( context.irBuilder( ).CreateCastelCall( "castelUndefined_create" ) );
        }
    }}

    context.irBuilder( ).SetInsertPoint( llvmCurrentBasicBlock, llvmCurrentPoint );

    return llvmFunctionBox;
}
