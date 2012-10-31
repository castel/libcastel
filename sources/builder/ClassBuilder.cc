#include <llvm/Support/TypeBuilder.h>
#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/builder/ClassBuilder.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/FunctionBuilder.hh"
#include "castel/builder/Scope.hh"
#include "castel/runtime/boxes/Class.hh"

using namespace castel;
using builder::ClassBuilder;

llvm::Value * ClassBuilder::create( builder::Context & context, builder::Scope * parentScope ) const
{
    llvm::Value * parent = mParent != nullptr ? mParent : llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box *, false >::get( context.llvmContext( ) ) ) ;
    llvm::Value * initializer = this->createInitializer( context, parentScope );

    llvm::Value * llvmClassBox = context.irBuilder( ).CreateCastelCall( "castelClass_create", parent, initializer, parentScope ? parentScope->environmentTable( ) : llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box ***, false >::get( context.llvmContext( ) ) ) );

    for ( auto & member : mMembers ) {
        if ( auto method = dynamic_cast< ast::expr::Class::Method * >( & member ) ) {
            if ( method->type( ) == ast::expr::Class::Member::Type::Binded ) {

                ast::expr::Function * astFunction = method->function( );

                llvm::Value * llvmName = context.irBuilder( ).CreateGlobalStringPtr( method->name( ) );
                llvm::Value * llvmFunction = builder::FunctionBuilder( ).useThis( true )
                    .parameters( astFunction->parameters( ) )
                    .statements( astFunction->statements( ) )
                .create( context, parentScope );

                context.irBuilder( ).CreateCastelCall( "castel_addMethod", llvmClassBox, llvmName, llvmFunction );

            }
        }
    }

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
                    llvm::Value * llvmName = context.irBuilder( ).CreateGlobalStringPtr( attribute->name( ) );
                    llvm::Value * llvmInitializer = codeGenerator.expression( attribute->initializer( ) );
                    context.irBuilder( ).CreateCastelCall( "castel_addMember", runtimeArguments_instance, llvmName, llvmInitializer );
                }
            }
        }

        context.irBuilder( ).CreateRetVoid( );
    }}

    context.irBuilder( ).SetInsertPoint( llvmCurrentBasicBlock, llvmCurrentPoint );

    return llvmFunction;
}
