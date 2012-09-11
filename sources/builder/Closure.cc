#include <list>
#include <stdexcept>

#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Value.h>

#include "castel/builder/Closure.hh"
#include "castel/builder/Context.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using builder::Closure;

void Closure::finalize( void )
{
    /* Creates a temporary instruction builder at the start of the llvm function */
    builder::Context temporaryContext( mContext );

    llvm::BasicBlock & entryBlock = mLLVMFunction.getEntryBlock( );
    temporaryContext.irBuilder( ).SetInsertPoint( & entryBlock, entryBlock.begin( ) );

    /* Duplicates parent environment table (adding an additional entry at the front for the current closure's environment) */
    llvm::Value * parentEnvironmentTable = mLLVMFunction.arg_begin( );

    llvm::Value * environmentTable = temporaryContext.irBuilder( ).CreateCastelAllocate< runtime::Box ** >( this->level( ) + 1 );
    mEnvironmentTable->replaceAllUsesWith( environmentTable );

    for ( int t = 0, T = this->level( ); t < T; ++ t ) {

        llvm::Value * parentEnvironmentEntryPointer = temporaryContext.irBuilder( ).CreateConstGEP1_64( parentEnvironmentTable, t );
        llvm::Value * environmentEntryPointer = temporaryContext.irBuilder( ).CreateConstGEP1_64( environmentTable, 1 + t );

        llvm::Value * parentEnvironmentEntry = temporaryContext.irBuilder( ).CreateLoad( parentEnvironmentEntryPointer );
        temporaryContext.irBuilder( ).CreateStore( parentEnvironmentEntry, environmentEntryPointer );

    }

    /* Separates variables into two list : one with local-access-only variables, and the other with all other variables */
    std::list< builder::Closure::Variable * > localVariables;
    std::list< builder::Closure::Variable * > escapingVariables;

    for ( auto & variableIterator : mVariables )
        if ( ! variableIterator.second->escape( ) )
            localVariables.push_back( variableIterator.second.get( ) );
        else
            escapingVariables.push_back( variableIterator.second.get( ) );

    /* Allocates local environment on the stack */
    llvm::Value * localEnvironment = temporaryContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( localVariables.size( ), true );

    /* Allocates escaping environment on the heap */
    llvm::Value * escapingEnvironment = temporaryContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( escapingVariables.size( ) );

    /* Stores environment pointer into the environment table */ {
        llvm::Value * environmentEntryPointer = temporaryContext.irBuilder( ).CreateConstGEP1_64( environmentTable, 0 );
        temporaryContext.irBuilder( ).CreateStore( escapingEnvironment, environmentEntryPointer );
    }

    /* Replaces all descriptors by the reals variables addresses */
    for ( auto & descriptorIterator : mDescriptors ) {

        builder::Closure::Descriptor & descriptor = * ( descriptorIterator.second );

        llvm::Value * realAddress;

        if ( descriptorIterator.second->variable( ).escape( ) ) {
            llvm::Value * remoteEnvironment = temporaryContext.irBuilder( ).CreateLoad( temporaryContext.irBuilder( ).CreateConstGEP1_64( environmentTable, descriptor.depth( ) ) );
            realAddress = temporaryContext.irBuilder( ).CreateGEP( remoteEnvironment, descriptor.variable( ).dummy( ) );
        } else {
            realAddress = temporaryContext.irBuilder( ).CreateGEP( localEnvironment, descriptor.variable( ).dummy( ) );
        }

        descriptor.dummy( )->replaceAllUsesWith( realAddress );

    }

    /* Set local variables indexes */ {
        int index = 0;
        for ( auto & variable : localVariables ) {
            variable->dummy( )->replaceAllUsesWith( llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, index ++ ) ) );
        }
    }

    /* Set escaping variables indexes */ {
        int index = 0;
        for ( auto & variable : escapingVariables ) {
            variable->dummy( )->replaceAllUsesWith( llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, index ++ ) ) );
        }
    }
}

void Closure::declare( std::string const & name, llvm::Value * initializer )
{
    if ( mVariables.find( name ) != mVariables.end( ) )
        throw std::runtime_error( "Multiple variable redefinition" );

    builder::Closure::Variable * variable = new builder::Closure::Variable( mContext.llvmContext( ), false );
    mVariables[ name ].reset( variable );

    if ( initializer ) {
        this->set( name, initializer );
    }
}

llvm::Value * Closure::get( std::string const & name )
{
    builder::Closure::Descriptor * descriptor = this->descriptor( name );

    return mContext.irBuilder( ).CreateLoad( descriptor->dummy( ) );
}

llvm::Value * Closure::set( std::string const & name, llvm::Value * value )
{
    builder::Closure::Descriptor * descriptor = this->descriptor( name );

    return mContext.irBuilder( ).CreateStore( value, descriptor->dummy( ) );
}

builder::Closure::Descriptor * Closure::descriptor( std::string const & name )
{
    auto descriptorsIterator = mDescriptors.find( name );

    if ( descriptorsIterator != mDescriptors.end( ) )
        return descriptorsIterator->second.get( );

    builder::Closure::Descriptor * descriptor = this->createDescriptor( name );
    mDescriptors[ name ].reset( descriptor );

    return descriptor;
}

builder::Closure::Descriptor * Closure::createDescriptor( std::string const & name, int depth )
{
    auto innerIterator = mVariables.find( name );

    if ( innerIterator == mVariables.end( ) )
        return this->recurseDescriptorCreation( name, depth );

    builder::Closure::Variable & variable = * ( innerIterator->second );

    if ( depth )
        variable.escape( true );

    return new builder::Closure::Descriptor( mContext.llvmContext( ), variable, depth );
}

builder::Closure::Descriptor * Closure::recurseDescriptorCreation( std::string const & name, int depth )
{
    if ( mParentClosure == nullptr )
        throw std::runtime_error( "Variable undeclared" );

    return mParentClosure->createDescriptor( name, depth + 1 );
}
