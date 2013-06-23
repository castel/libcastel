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
    if ( mStatements == nullptr )
        throw std::runtime_error( "CodeBuilders must have a 'statements' field when built" );

    gen::SVisitor visitor( context, module, irBuilder, scope );

    for ( auto & statement : * mStatements ) {
        statement->accept( visitor );
    }
}
