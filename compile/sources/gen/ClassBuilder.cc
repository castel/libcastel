#include <stdexcept>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include "castel/ast/expr/literal/Function.hh"
#include "castel/ast/tools/Hold.hh"
#include "castel/ast/tools/List.hh"
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
    if ( ! mMembers )
        throw std::runtime_error( "ClassBuilders must have a 'members' field when built" );

    llvm::Value * parent = mParent != nullptr ? mParent : gen::helper::null< runtime::Box * >( context );
    llvm::Value * initializer = this->createInitializer( context, module, parentScope );

    llvm::Value * classBox = gen::helper::call( context, module, irBuilder, "Castel_Class_create",
        parent, initializer, parentScope.environmentTable( ) );

    for ( auto & member : * mMembers ) {
        // @todo Maybe find a better way than using unique_ptr#get ?
        if ( auto method = dynamic_cast< ast::expr::literal::Class::Method * >( member.get( ) ) ) {
            if ( method->host( ) == ast::expr::literal::Class::Member::Host::Instance ) {

                ast::tools::Hold< ast::expr::literal::Function > const & functionAst = method->function( );

                llvm::Value * name = gen::helper::string( irBuilder, method->name( ) );
                llvm::Value * function = gen::FunctionBuilder( ).useThis( true )
                    .parameters( & functionAst->parameters( ) )
                    .statements( & functionAst->statements( ) )
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
    function->setPersonalityFn( module->getFunction( "Castel_personality" ) );

    llvm::BasicBlock * block = llvm::BasicBlock::Create( context, "", function );
    llvm::IRBuilder< > irBuilder( block, block->begin( ) );

    llvm::Function::arg_iterator runtimeArguments = function->arg_begin( );
    llvm::Value * runtimeArguments_instance = runtimeArguments ++;
    llvm::Value * runtimeArguments_parentEnvironmentTable = runtimeArguments ++;
    llvm::Value * runtimeArguments_argc = runtimeArguments ++;
    llvm::Value * runtimeArguments_argv = runtimeArguments ++;

    {{ gen::Scope scope( context, module, block, parentScope, runtimeArguments_parentEnvironmentTable );

       scope.declare( irBuilder, "this", runtimeArguments_instance );

       for ( auto & member : * mMembers ) {
           // @todo Maybe find a better way than using unique_ptr#get ?
           if ( auto attribute = dynamic_cast< ast::expr::literal::Class::Attribute * >( member.get( ) ) ) {
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

       for ( auto & member : * mMembers ) {
           // @todo Maybe find a better way than using unique_ptr#get ?
           if ( auto constructor = dynamic_cast< ast::expr::literal::Class::Constructor * >( member.get( ) ) ) {
               gen::helper::call( context, module, irBuilder, "Castel_Operator_call",
                   gen::GPEVisitor( context, module, irBuilder, scope ).run( * ( constructor->function( ) ) ),
                   runtimeArguments_argc,
                   runtimeArguments_argv
               );
           }
       }

       irBuilder.CreateRetVoid( );
    }}

    return function;
}
