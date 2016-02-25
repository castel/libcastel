#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include "castel/ast/tools/List.hh"
#include "castel/ast/Statement.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/ModuleBuilder.hh"
#include "castel/runtime/interfaces/all.prelude.hh"
#include "castel/runtime/Module.hh"
#include "castel/toolchain/Compiler.hh"
#include "castel/toolchain/Source.hh"

using namespace castel;
using toolchain::Compiler;

Compiler::Compiler( void )
    : mContext( )
{
    llvm::StructType::create( mContext, "_Unwind_Context" );
    llvm::StructType::create( mContext, "_Unwind_Exception" );

    llvm::StructType::create( mContext, "Box" );
}

llvm::Module * Compiler::build( ast::tools::List< ast::Statement > const & statements, std::string const & name )
{
    llvm::Module * module = new llvm::Module( name, mContext );

    #define TOSTRING( X ) #X

    #define CASTEL_FUNCTION( NAME, RETURN, PARAMETERS ) {                                                                                           \
        llvm::Function::Create( gen::helper::type< RETURN PARAMETERS >( mContext ), llvm::GlobalValue::ExternalLinkage, TOSTRING( NAME ), module ); \
        /*function->setPersonalityFn( module->getFunction( "Castel_personality" ) );*/ \
    }

    #define CASTEL_TYPE( TYPE, CONSTRUCTOR )                                   \
        CASTEL_FUNCTION( Castel_##TYPE##_create, runtime::Box *, CONSTRUCTOR )

    #define CASTEL_SHIPPED_FUNCTION( TYPE, NAME )                                                                     \
        CASTEL_FUNCTION( Castel_##TYPE##_##NAME, runtime::Box *, ( runtime::Box ***, std::uint8_t, runtime::Box * ) )

    #include "castel/runtime/interfaces/all.def"

    #undef CASTEL_SHIPPED_FUNCTION

    #undef CASTEL_TYPE

    #undef CASTEL_FUNCTION

    #undef TOSTRING

    gen::ModuleBuilder( name )
        .globals( mGlobals )
        .statements( & statements )
    .build( mContext, module );

    return module;
}
