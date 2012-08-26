#include <list>
#include <stdexcept>

#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Value.h>

#include <mpllvm/mpllvm.hh>

#include "castel/engine/Closure.hh"
#include "castel/engine/LLVMHelpers.hh"
#include "castel/engine/Value.hh"

#include <iostream>

using namespace castel;
using engine::Closure;

typedef engine::Value * BoxPointer;
typedef BoxPointer Environment[];
typedef Environment * EnvironmentTable[];

void Closure::finalize( void )
{
    /* Creates a temporary instruction builder at the start of the llvm function */
    llvm::BasicBlock & entryBlock = mLLVMFunction.getEntryBlock( );
    llvm::IRBuilder< > temporaryBuilder( & entryBlock, entryBlock.begin( ) );

    /* Instanciates an object wrapping common Castel's LLVM operations */
    engine::LLVMHelpers llvmHelpers( mGenerationEngine.llvmContext( ), temporaryBuilder, mGenerationEngine.module( ) );

    /* Duplicates parent environment table (adding an additional entry at the front for the current closure's environment) */
    llvm::Value * parentEnvironmentTable = mLLVMFunction.arg_begin( );

    llvm::Value * environmentTable = llvmHelpers.allocateArray< engine::Value ** >( this->level( ) + 1 );
    mEnvironmentTable->replaceAllUsesWith( environmentTable );

    for ( int t = 0, T = this->level( ); t < T; ++ t ) {

        llvm::Value * parentEnvironmentEntryPointer = mpllvm::GEP< std::int64_t >::build( mGenerationEngine.llvmContext( ), temporaryBuilder, parentEnvironmentTable, t );
        llvm::Value * environmentEntryPointer = mpllvm::GEP< std::int64_t >::build( mGenerationEngine.llvmContext( ), temporaryBuilder, environmentTable, 1 + t );

        llvm::Value * parentEnvironmentEntry = temporaryBuilder.CreateLoad( parentEnvironmentEntryPointer );
        temporaryBuilder.CreateStore( parentEnvironmentEntry, environmentEntryPointer );

    }

    /* Separates variables into two list : one with local-access-only variables, and the other with all other variables */
    std::list< engine::Closure::Variable * > localVariables;
    std::list< engine::Closure::Variable * > escapingVariables;

    for ( auto & variableIterator : mVariables )
        if ( ! variableIterator.second->escape( ) )
            localVariables.push_back( variableIterator.second.get( ) );
        else
            escapingVariables.push_back( variableIterator.second.get( ) );

    /* Allocates local environment on the stack */
    llvm::Value * localEnvironment = llvmHelpers.allocateArray< engine::Value * >( localVariables.size( ), true );

    /* Allocates escaping environment on the heap */
    llvm::Value * escapingEnvironment = llvmHelpers.allocateArray< engine::Value * >( escapingVariables.size( ) );

    /* Stores environment pointer into the environment table */ {
        llvm::Value * environmentEntryPointer = mpllvm::GEP< std::int64_t >::build( mGenerationEngine.llvmContext( ), temporaryBuilder, environmentTable, 0 );
        temporaryBuilder.CreateStore( escapingEnvironment, environmentEntryPointer );
    }

    /* Replaces all descriptors by the reals variables addresses */
    for ( auto & descriptorIterator : mDescriptors ) {

        engine::Closure::Descriptor & descriptor = * ( descriptorIterator.second );

        llvm::Value * realAddress;

        if ( descriptorIterator.second->variable( ).escape( ) ) {
            llvm::Value * remoteEnvironment = temporaryBuilder.CreateLoad( mpllvm::GEP< std::int64_t >::build( mGenerationEngine.llvmContext( ), temporaryBuilder, environmentTable, descriptor.depth( ) ) );
            realAddress = mpllvm::GEP< llvm::Value * >::build( mGenerationEngine.llvmContext( ), temporaryBuilder, remoteEnvironment, descriptor.variable( ).dummy( ) );
        } else {
            realAddress = mpllvm::GEP< llvm::Value * >::build( mGenerationEngine.llvmContext( ), temporaryBuilder, localEnvironment, descriptor.variable( ).dummy( ) );
        }

        descriptor.dummy( )->replaceAllUsesWith( realAddress );

    }

    /* Set local variables indexes */ {
        int index = 0;
        for ( auto & variable : localVariables ) {
            variable->dummy( )->replaceAllUsesWith( llvm::ConstantInt::get( mGenerationEngine.llvmContext( ), llvm::APInt( 32, index ++ ) ) );
        }
    }

    /* Set escaping variables indexes */ {
        int index = 0;
        for ( auto & variable : escapingVariables ) {
            variable->dummy( )->replaceAllUsesWith( llvm::ConstantInt::get( mGenerationEngine.llvmContext( ), llvm::APInt( 32, index ++ ) ) );
        }
    }
}

void Closure::declare( std::string const & name, llvm::Value * initializer )
{
    if ( mVariables.find( name ) != mVariables.end( ) )
        throw std::runtime_error( "Multiple variable redefinition" );

    engine::Closure::Variable * variable = new engine::Closure::Variable( mGenerationEngine.llvmContext( ), false );
    mVariables[ name ].reset( variable );

    if ( initializer ) {
        this->set( name, initializer );
    }
}

llvm::Value * Closure::get( std::string const & name )
{
    engine::Closure::Descriptor * descriptor = this->descriptor( name );

    return mGenerationEngine.irBuilder( ).CreateLoad( descriptor->dummy( ) );
}

llvm::Value * Closure::set( std::string const & name, llvm::Value * value )
{
    engine::Closure::Descriptor * descriptor = this->descriptor( name );

    return mGenerationEngine.irBuilder( ).CreateStore( value, descriptor->dummy( ) );
}

engine::Closure::Descriptor * Closure::descriptor( std::string const & name )
{
    auto descriptorsIterator = mDescriptors.find( name );

    if ( descriptorsIterator != mDescriptors.end( ) )
        return descriptorsIterator->second.get( );

    engine::Closure::Descriptor * descriptor = this->createDescriptor( name );
    mDescriptors[ name ].reset( descriptor );

    return descriptor;
}

engine::Closure::Descriptor * Closure::createDescriptor( std::string const & name, int depth )
{
    auto innerIterator = mVariables.find( name );

    if ( innerIterator == mVariables.end( ) )
        return this->recurseDescriptorCreation( name, depth );

    engine::Closure::Variable & variable = * ( innerIterator->second );

    if ( depth )
        variable.escape( true );

    return new engine::Closure::Descriptor( mGenerationEngine.llvmContext( ), variable, depth );
}

engine::Closure::Descriptor * Closure::recurseDescriptorCreation( std::string const & name, int depth )
{
    if ( mParentClosure == nullptr )
        throw std::runtime_error( "Variable undeclared" );

    return mParentClosure->createDescriptor( name, depth + 1 );
}
