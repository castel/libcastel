#include <stdexcept>

#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include "castel/gen/CodeBuilder.hh"
#include "castel/gen/Scope.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::CodeBuilder;

void CodeBuilder::build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope )
{
    if ( ! mStatements )
        throw std::runtime_error( "CodeBuilders must have a 'statements' field when built" );

    for ( auto const & statement : * mStatements ) {
        gen::SVisitor( context, module, irBuilder, scope ).run( * statement );
    }
}
