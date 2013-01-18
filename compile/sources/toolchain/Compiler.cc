#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Module.h>

#include "castel/gen/helper/type.hh"
#include "castel/gen/ModuleBuilder.hh"
#include "castel/runtime/Module.hh"
#include "castel/runtime/capi.hh"
#include "castel/toolchain/Compiler.hh"
#include "castel/toolchain/Source.hh"

using namespace castel;
using toolchain::Compiler;

Compiler::Compiler( void )
    : mContext( )
{
    llvm::StructType::create( mContext, "Box" );
}

llvm::Module * Compiler::build( toolchain::Source const & source, std::string const & name )
{
    llvm::Module * module = new llvm::Module( source.name( ), mContext );

    #define TOSTRING( X ) #X
    #define DECLARE( NAME ) llvm::Function::Create( gen::helper::type< decltype( NAME ) >( mContext ), llvm::GlobalValue::ExternalLinkage, TOSTRING( NAME ), module );

    #define CASTEL_FUNCTION( NAME, RETURN, PARAMETERS ) DECLARE( NAME )
    #define CASTEL_EXTERNAL( NAME ) DECLARE( NAME )

        #include <castel/runtime/capi.def>

    #undef CASTEL_EXTERNAL
    #undef CASTEL_FUNCTION

    #undef DECLARE
    #undef TOSTRING

    gen::ModuleBuilder( name )
        .globals( mGlobals )
        .statements( source.parse( ) )
    .build( mContext, module );

    llvm::verifyModule( * module );

    return module;
}
