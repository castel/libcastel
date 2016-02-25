#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>

#include "castel/runtime/Box.hh"
#include "castel/runtime/Module.hh"
#include "castel/toolchain/Runner.hh"

using namespace castel;
using toolchain::Runner;

void Runner::staticInitializer( void )
{
    static bool initialized = false;

    if ( initialized )
        return ;

    llvm::InitializeNativeTarget( );
    llvm::InitializeNativeTargetAsmPrinter( );

    initialized = true;
}

runtime::Box * Runner::staticDependencyInitializer( Runner * runner, char const * global )
{
    return runner->mGlobals[ global ]( );
}

Runner::Runner( void )
{
    Runner::staticInitializer( );
}

runtime::Box * Runner::run( llvm::Module * module, std::string const & name )
{
    std::string errString;

    llvm::ExecutionEngine * executionEngine = llvm::EngineBuilder( std::unique_ptr< llvm::Module >( module ) )
        .setErrorStr( &( errString ) )
    .create( );

    if ( ! executionEngine )
        throw std::runtime_error( errString );

    for ( auto & global : mGlobals )
        executionEngine->addGlobalMapping( module->getFunction( global.first + "_generator" ), reinterpret_cast< void * >( & Runner::staticDependencyInitializer ) );

    executionEngine->finalizeObject( );

    void * programPtr = executionEngine->getPointerToFunction( module->getFunction( name ) );
    return reinterpret_cast< runtime::Module::Signature * >( programPtr )( this );
}
