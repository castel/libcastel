#include <list>
#include <stdexcept>
#include <string>

#include <llvm/ADT/APInt.h>
#include <llvm/TypeBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Type.h>
#include <llvm/Value.h>

#include "castel/runtime/Box.hh"
#include "castel/gen/helper/allocate.hh"
#include "castel/gen/helper/i32.hh"
#include "castel/gen/helper/null.hh"
#include "castel/gen/Scope.hh"

using namespace castel;
using gen::Scope;

Scope::~Scope( void )
{
    llvm::IRBuilder< > irBuilder( mBasicBlock, mBasicBlock->begin( ) );

    std::list< gen::Scope::Variable * > localVariables;
    std::list< gen::Scope::Variable * > escapingVariables;

    for ( auto & variableIterator : mVariables ) {
        switch ( variableIterator.second->status( ) ) {

            case gen::Scope::Variable::Status::Local:
                localVariables.push_back( variableIterator.second.get( ) );
            break;

            case gen::Scope::Variable::Status::Escaping:
                escapingVariables.push_back( variableIterator.second.get( ) );
            break;

        }
    }

    llvm::Value * escapingEnvironment = ( ! escapingVariables.empty( ) )
        ? gen::helper::allocate< runtime::Box * >( mContext, mModule, irBuilder, escapingVariables.size( ) )
        : gen::helper::null< runtime::Box ** >( mContext );

    llvm::Value * localEnvironment = ( ! localVariables.empty( ) )
        ? gen::helper::allocate< runtime::Box * >( mContext, mModule, irBuilder, localVariables.size( ), true )
        : gen::helper::null< runtime::Box ** >( mContext );

    llvm::Value * environmentTable = nullptr;
    if ( mPreserveEnvironmentTable ) {

        environmentTable = gen::helper::allocate< runtime::Box ** >( mContext, mModule, irBuilder, mScopeLevel + 1 );
        mEnvironmentTable->replaceAllUsesWith( environmentTable );

        irBuilder.CreateStore( escapingEnvironment, environmentTable );

        for ( unsigned char t = 0, T = mScopeLevel; t < T; ++ t ) {

            llvm::Value * parentEnvironmentEntryPointer = irBuilder.CreateConstGEP1_32( mParentEnvironmentTable, t );
            llvm::Value * environmentEntryPointer = irBuilder.CreateConstGEP1_32( environmentTable, 1 + t );

            llvm::Value * parentEnvironmentEntry = irBuilder.CreateLoad( parentEnvironmentEntryPointer );
            irBuilder.CreateStore( parentEnvironmentEntry, environmentEntryPointer );

        }

    } else {

        mEnvironmentTable->replaceAllUsesWith( gen::helper::null< runtime::Box *** >( mContext ) );

    }

    for ( auto & descriptorIterator : mDescriptors ) {

        gen::Scope::Descriptor & descriptor = * ( descriptorIterator.second );

        llvm::Value * realAddress = nullptr;
        if ( descriptor.variable( ).status( ) == gen::Scope::Variable::Status::Escaping ) {
            llvm::Value * targetEnvironment = irBuilder.CreateLoad( irBuilder.CreateConstGEP1_32( environmentTable, descriptor.depth( ) ) );
            realAddress = irBuilder.CreateGEP( targetEnvironment, descriptor.variable( ).dummy( ) );
        } else {
            realAddress = irBuilder.CreateGEP( localEnvironment, descriptor.variable( ).dummy( ) );
        }

        descriptor.dummy( )->replaceAllUsesWith( realAddress );

    }

    int localVariableIndex = 0;
    for ( auto & variable : localVariables )
        variable->dummy( )->replaceAllUsesWith( gen::helper::i32( mContext, localVariableIndex ++ ) );

    int escapingVariableIndex = 0;
    for ( auto & variable : escapingVariables )
        variable->dummy( )->replaceAllUsesWith( gen::helper::i32( mContext, escapingVariableIndex ++ ) );
}

Scope & Scope::declare( llvm::IRBuilder< > & irBuilder, std::string const & name, llvm::Value * initializer )
{
    if ( mVariables.find( name ) != mVariables.end( ) )
        throw std::runtime_error( "Multiple variable redefinition" );

    gen::Scope::Variable * variable = new gen::Scope::Variable( mContext );
    mVariables[ name ].reset( variable );

    if ( initializer )
        this->set( irBuilder, name, initializer );

    return * this;
}

llvm::Value * Scope::get( llvm::IRBuilder< > & irBuilder, std::string const & name )
{
    gen::Scope::Descriptor * descriptor = this->descriptor( name );

    return irBuilder.CreateLoad( descriptor->dummy( ) );
}

llvm::Value * Scope::set( llvm::IRBuilder< > & irBuilder, std::string const & name, llvm::Value * value )
{
    gen::Scope::Descriptor * descriptor = this->descriptor( name );

    return irBuilder.CreateStore( value, descriptor->dummy( ) );
}

void Scope::preserveEnvironmentTable( void )
{
    if ( ! mPreserveEnvironmentTable ) {
        mPreserveEnvironmentTable = true;

        if ( mParentScope ) {
            mParentScope->preserveEnvironmentTable( );
        }
    }
}

gen::Scope::Descriptor * Scope::descriptor( std::string const & name )
{
    auto descriptorsIterator = mDescriptors.find( name );

    if ( descriptorsIterator != mDescriptors.end( ) )
        return descriptorsIterator->second.get( );

    gen::Scope::Descriptor * descriptor = this->createDescriptor( name );
    mDescriptors[ name ].reset( descriptor );

    if ( descriptor->variable( ).status( ) == gen::Scope::Variable::Status::Escaping )
        this->preserveEnvironmentTable( );

    return descriptor;
}

gen::Scope::Descriptor * Scope::createDescriptor( std::string const & name, int depth )
{
    auto innerIterator = mVariables.find( name );

    if ( innerIterator == mVariables.end( ) )
        return this->recurseDescriptorCreation( name, depth );

    gen::Scope::Variable & variable = * ( innerIterator->second );

    if ( depth )
        variable.status( gen::Scope::Variable::Status::Escaping );

    return new gen::Scope::Descriptor( mContext, variable, depth );
}

gen::Scope::Descriptor * Scope::recurseDescriptorCreation( std::string const & name, int depth )
{
    if ( mParentScope == nullptr )
        throw std::runtime_error( "Undeclared variable '" + name + "'" );

    return mParentScope->createDescriptor( name, depth + 1 );
}
