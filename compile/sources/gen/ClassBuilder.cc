#include <llvm/IRBuilder.h>
#include <llvm/Constants.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/expr/literal/Function.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/string.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/ClassBuilder.hh"
#include "castel/gen/FunctionBuilder.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/gen/Scope.hh"
#include "castel/runtime/boxes/Class.hh"

using namespace castel;
using gen::ClassBuilder;

llvm::Value * ClassBuilder::build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & parentScope ) const
{
    llvm::Value * parent = mParent != nullptr ? mParent : gen::helper::null< runtime::Box * >( context );
    llvm::Value * initializer = this->createInitializer( context, module, parentScope );

    llvm::Value * classBox = gen::helper::call( context, module, irBuilder, "Castel_Class_create",
        parent, initializer, parentScope.environmentTable( ) );

    for ( auto & member : mMembers ) {
        if ( auto method = dynamic_cast< ast::expr::literal::Class::Method * >( & member ) ) {
            if ( method->host( ) == ast::expr::literal::Class::Member::Host::Instance ) {

                ast::expr::literal::Function * functionAst = method->function( );

                llvm::Value * name = gen::helper::string( irBuilder, method->name( ) );
                llvm::Value * function = gen::FunctionBuilder( ).useThis( true )
                    .parameters( functionAst->parameters( ) )
                    .statements( functionAst->statements( ) )
                .build( context, module, irBuilder, parentScope );

                gen::helper::call( context, module, irBuilder, "Castel_addMethod",
                    classBox, name, function );

            }
        }
    }

    return classBox;
}

llvm::Value * ClassBuilder::createInitializer( llvm::LLVMContext & context, llvm::Module * module, gen::Scope & parentScope ) const
{
    llvm::Function * function = llvm::Function::Create( gen::helper::type< runtime::boxes::Class::InitializerSignature >( context ), llvm::GlobalVariable::ExternalLinkage, mName + "_initializer", module );
    llvm::BasicBlock * block = llvm::BasicBlock::Create( context, "", function );
    llvm::IRBuilder< > irBuilder( block, block->begin( ) );

    llvm::Function::ArgumentListType::iterator runtimeArguments = function->getArgumentList( ).begin( );
    llvm::Value * runtimeArguments_instance = runtimeArguments ++;
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;

    {{ gen::Scope scope( context, module, block, parentScope, runtimeArguments_parentEnvironmentTable );

       scope.declare( irBuilder, "this", runtimeArguments_instance );

       for ( auto & member : mMembers ) {
           if ( auto attribute = dynamic_cast< ast::expr::literal::Class::Attribute * >( & member ) ) {
               if ( attribute->host( ) == ast::expr::literal::Class::Member::Host::Instance ) {
                   gen::helper::call( context, module, irBuilder, "Castel_addMember",
                       runtimeArguments_instance,
                       gen::helper::string( irBuilder, attribute->name( ) ),
                       ( attribute->initializer( )
                           ? gen::GPEVisitor( context, module, irBuilder, scope ).run( * ( attribute->initializer( ) ) )
                           : gen::helper::call( context, module, irBuilder, "Castel_Undefined_create" )
                       )
                   );
               }
           }
       }

       irBuilder.CreateRetVoid( );
    }}

    return function;
}
