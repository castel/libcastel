#include <list>
#include <stdexcept>
#include <string>

#include <llvm/ADT/APInt.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Type.h>
#include <llvm/Value.h>

#include "castel/builder/Scope.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using builder::Scope;

Scope::~Scope( void )
{
    llvm::BasicBlock * llvmCurrentBasicBlock = mContext.irBuilder( ).GetInsertBlock( );
    llvm::BasicBlock::iterator llvmCurrentPoint = mContext.irBuilder( ).GetInsertPoint( );

    llvm::BasicBlock::iterator llvmBasicBlockBegin = mBasicBlock.begin( );
    mContext.irBuilder( ).SetInsertPoint( & mBasicBlock, llvmBasicBlockBegin );

    std::list< builder::Scope::Variable * > localVariables;
    std::list< builder::Scope::Variable * > escapingVariables;

    for ( auto & variableIterator : mVariables ) {
        switch ( variableIterator.second->status( ) ) {
            case builder::Scope::Variable::Status::Local:
                localVariables.push_back( variableIterator.second.get( ) );
            break;
            case builder::Scope::Variable::Status::Escaping:
                escapingVariables.push_back( variableIterator.second.get( ) );
            break;
        }
    }

    llvm::Value * escapingEnvironment = ( ! escapingVariables.empty( ) )
        ? mContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( escapingVariables.size( ) )
        : llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box **, false >::get( mContext.llvmContext( ) ) );

    llvm::Value * localEnvironment = ( ! localVariables.empty( ) )
        ? mContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( localVariables.size( ), true )
        : llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box **, false >::get( mContext.llvmContext( ) ) );

    llvm::Value * environmentTable = nullptr;
    if ( mPreserveEnvironmentTable ) {

        environmentTable = mContext.irBuilder( ).CreateCastelAllocate< runtime::Box ** >( mLevel + 1 );
        mEnvironmentTable->replaceAllUsesWith( environmentTable );

        mContext.irBuilder( ).CreateStore( escapingEnvironment, environmentTable );

        for ( unsigned char t = 0, T = mLevel; t < T; ++ t ) {

            llvm::Value * parentEnvironmentEntryPointer = mContext.irBuilder( ).CreateConstGEP1_64( mParentEnvironmentTable, t );
            llvm::Value * environmentEntryPointer = mContext.irBuilder( ).CreateConstGEP1_64( environmentTable, 1 + t );

            llvm::Value * parentEnvironmentEntry = mContext.irBuilder( ).CreateLoad( parentEnvironmentEntryPointer );
            mContext.irBuilder( ).CreateStore( parentEnvironmentEntry, environmentEntryPointer );

        }

    }

    for ( auto & descriptorIterator : mDescriptors ) {

        builder::Scope::Descriptor & descriptor = * ( descriptorIterator.second );

        llvm::Value * realAddress = nullptr;
        if ( descriptor.variable( ).status( ) == builder::Scope::Variable::Status::Escaping ) {
            llvm::Value * targetEnvironment = mContext.irBuilder( ).CreateLoad( mContext.irBuilder( ).CreateConstGEP1_64( environmentTable, descriptor.depth( ) ) );
            realAddress = mContext.irBuilder( ).CreateGEP( targetEnvironment, descriptor.variable( ).dummy( ) );
        } else {
            realAddress = mContext.irBuilder( ).CreateGEP( localEnvironment, descriptor.variable( ).dummy( ) );
        }

        descriptor.dummy( )->replaceAllUsesWith( realAddress );

    }

    int localVariableIndex = 0;
    for ( auto & variable : localVariables )
        variable->dummy( )->replaceAllUsesWith( llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, localVariableIndex ++ ) ) );

    int escapingVariableIndex = 0;
    for ( auto & variable : escapingVariables )
        variable->dummy( )->replaceAllUsesWith( llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, escapingVariableIndex ++ ) ) );

    mContext.irBuilder( ).SetInsertPoint( llvmCurrentBasicBlock, llvmCurrentPoint );
}

Scope & Scope::declare( std::string const & name, llvm::Value * initializer )
{
    if ( mVariables.find( name ) != mVariables.end( ) )
        throw std::runtime_error( "Multiple variable redefinition" );

    builder::Scope::Variable * variable = new builder::Scope::Variable( mContext.llvmContext( ) );
    mVariables[ name ].reset( variable );

    if ( initializer ) {
        this->set( name, initializer );
    }

    return * this;
}

llvm::Value * Scope::get( std::string const & name )
{
    builder::Scope::Descriptor * descriptor = this->descriptor( name );

    return mContext.irBuilder( ).CreateLoad( descriptor->dummy( ) );
}

llvm::Value * Scope::set( std::string const & name, llvm::Value * value )
{
    builder::Scope::Descriptor * descriptor = this->descriptor( name );

    return mContext.irBuilder( ).CreateStore( value, descriptor->dummy( ) );
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

builder::Scope::Descriptor * Scope::descriptor( std::string const & name )
{
    auto descriptorsIterator = mDescriptors.find( name );

    if ( descriptorsIterator != mDescriptors.end( ) )
        return descriptorsIterator->second.get( );

    builder::Scope::Descriptor * descriptor = this->createDescriptor( name );
    mDescriptors[ name ].reset( descriptor );

    if ( descriptor->variable( ).status( ) == builder::Scope::Variable::Status::Escaping )
        this->preserveEnvironmentTable( );

    return descriptor;
}

builder::Scope::Descriptor * Scope::createDescriptor( std::string const & name, int depth )
{
    auto innerIterator = mVariables.find( name );

    if ( innerIterator == mVariables.end( ) )
        return this->recurseDescriptorCreation( name, depth );

    builder::Scope::Variable & variable = * ( innerIterator->second );

    if ( depth )
        variable.status( builder::Scope::Variable::Status::Escaping );

    return new builder::Scope::Descriptor( mContext.llvmContext( ), variable, depth );
}

builder::Scope::Descriptor * Scope::recurseDescriptorCreation( std::string const & name, int depth )
{
    if ( mParentScope == nullptr )
        throw std::runtime_error( "Undeclared variable '" + name + "'" );

    return mParentScope->createDescriptor( name, depth + 1 );
}
