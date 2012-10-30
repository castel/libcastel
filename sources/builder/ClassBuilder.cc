#include <llvm/Value.h>

#include "castel/builder/ClassBuilder.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"
#include "castel/runtime/boxes/Class.hh"

using namespace castel;
using builder::ClassBuilder;

llvm::Value * ClassBuilder::create( builder::Context & context, builder::Scope * parentScope ) const
{
    llvm::Value * initializer = this->createInitializer( context, parentScope );
    llvm::Value * llvmClassBox = context.irBuilder( ).CreateCastelCall( "castelClass_create", initializer );

    return llvmClassBox;
}

llvm::Value * ClassBuilder::createInitializer( builder::Context & context, builder::Scope * parentScope ) const
{
    llvm::BasicBlock * llvmCurrentBasicBlock = context.irBuilder( ).GetInsertBlock( );
    llvm::BasicBlock::iterator llvmCurrentPoint = context.irBuilder( ).GetInsertPoint( );

    llvm::Function * llvmFunction = context.declareGlobalFunction< runtime::boxes::Class::InitializerSignature >( mName + "_initializer", llvm::Function::ExternalLinkage );
    llvm::BasicBlock * llvmBlock = llvm::BasicBlock::Create( context.llvmContext( ), "", llvmFunction );

    context.irBuilder( ).SetInsertPoint( llvmBlock );

    llvm::Function::ArgumentListType::iterator runtimeArguments = llvmFunction->getArgumentList( ).begin( );
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;
    llvm::Value * runtimeArguments_instance = runtimeArguments ++;

    {{  builder::Scope scope( context, * llvmBlock, parentScope );
        scope.parentEnvironmentTable( runtimeArguments_parentEnvironmentTable );

        scope.declare( "this", runtimeArguments_instance );

        for ( auto & member : mMembers ) {
            if ( auto attribute = dynamic_cast< ast::expr::Class::Attribute * >( & member ) ) {
                if ( attribute->type( ) == ast::expr::Class::Member::Type::Binded ) {
                    builder::CodeGenerator codeGenerator( context, scope );
                    llvm::Value * name = context.irBuilder( ).CreateGlobalStringPtr( attribute->name( ) );
                    llvm::Value * initializer = codeGenerator.expression( attribute->initializer( ) );
                    context.irBuilder( ).CreateCastelCall( "castel_addProperty", name, initializer );
                }
            }
        }
    }}

    return llvmFunction;
}
