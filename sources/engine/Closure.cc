#include <stdexcept>
#include <string>

#include <llvm/Support/IRBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Value.h>
#include <mpllvm/mpllvm.hh>

#include "castel/engine/Closure.hh"
#include "castel/engine/LLVMHelpers.hh"
#include "castel/utils/mpllvmExtensions.hh"

using namespace castel;
using castel::engine::Closure;

void Closure::finalize( void )
{
    mFinalized = true;

    llvm::BasicBlock & entryBlock = mLLVMFunction->getEntryBlock( );
    llvm::IRBuilder< > temporaryBuilder( & entryBlock, entryBlock.begin( ) );

    engine::LLVMHelpers llvmHelpers( mGenerationEngine.llvmContext( ), temporaryBuilder, mGenerationEngine.module( ) );

    if ( ! mLocalValues.empty( ) ) {

        llvm::Value * memory = llvmHelpers.allocateArray( mpllvm::get< engine::Value * >( mGenerationEngine.llvmContext( ) ), mLocalValues.size( ), true );

        int variableId = 0;

        for ( auto & localIterator : mLocalValues ) {
            llvm::Value * variableOffset = temporaryBuilder.CreateConstGEP2_32( memory, 0, variableId ++ );
            localIterator.second->replaceAllUsesWith( variableOffset );
        }

    }

    if ( ! mEscapingValues.empty( ) ) {

        llvm::Value * memory = llvmHelpers.allocateArray( mpllvm::get< engine::Value * >( mGenerationEngine.llvmContext( ) ), mEscapingValues.size( ) );

        int variableId = 0;

    }

}
#include <iostream>
void Closure::declare( std::string const & name, llvm::Value * initializer )
{
    if ( mFinalized )
        throw std::runtime_error( "Closure has already been finalized" );

    auto it = mLocalValues.find( name );

    if ( it != mLocalValues.end( ) )
        throw std::runtime_error( "Variable redefinition" );

    llvm::Value * dummyAddress = mGenerationEngine.irBuilder( ).CreateAlloca( mpllvm::get< engine::Value * >( mGenerationEngine.llvmContext( ) ) );
    mLocalValues[ name ] = dummyAddress;

    if ( initializer ) {
        mGenerationEngine.irBuilder( ).CreateStore( initializer, dummyAddress );
    }
}

llvm::Value * Closure::get( std::string const & name )
{
    if ( mFinalized )
        throw std::runtime_error( "Closure has already been finalized" );

    std::cout << name << std::endl;

    return mGenerationEngine.irBuilder( ).CreateLoad( this->variableAddressor( name ) );
}

llvm::Value * Closure::set( std::string const & name, llvm::Value * value )
{
    if ( mFinalized )
        throw std::runtime_error( "Closure has already been finalized" );

    return mGenerationEngine.irBuilder( ).CreateStore( value, this->variableAddressor( name ) );
}

llvm::Value * Closure::variableAddressor( std::string const & name )
{
    auto localIterator = mLocalValues.find( name );

    if ( localIterator != mLocalValues.end( ) )
        return localIterator->second;

    auto escapingIterator = mEscapingValues.find( name );

    if ( escapingIterator != mEscapingValues.end( ) )
        return escapingIterator->second;

    return this->recurseAddressorSearch( name );
}

llvm::Value * Closure::recurseAddressorSearch( std::string const & name )
{
    if ( ! mParentClosure )
        throw std::runtime_error( "Undefined variable" );

    return mParentClosure->escapedVariableAddressor( name );
}

llvm::Value * Closure::escapedVariableAddressor( std::string const & name )
{
    auto escapingIterator = mEscapingValues.find( name );

    if ( escapingIterator != mEscapingValues.end( ) )
        return escapingIterator->second;

    auto localIterator = mLocalValues.find( name );

    if ( localIterator == mLocalValues.end( ) )
        return this->recurseAddressorSearch( name );

    llvm::Value * addressor = localIterator->second;
    mLocalValues.erase( localIterator );
    mEscapingValues[ name ] = addressor;

    return addressor;
}
