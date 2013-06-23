#include <cstdlib>
#include <iostream>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Module.h>

#include "castel/ast/tools/List.hh"
#include "castel/ast/Statement.hh"
#include "castel/toolchain/Compiler.hh"
#include "castel/toolchain/Source.hh"

using castel::ast::tools::List;
using castel::ast::Statement;
using castel::toolchain::Compiler;
using castel::toolchain::Source;

int main( int argc, char ** argv )
{
    if ( argc < 2 ) {
        std::cerr
            << "Usage: " << argv[ 0 ] << " <module name>" << std::endl
            << "Converts castel file from standard input into LLVM IR" << std::endl;
        std::exit( 1 );
    }

    Compiler compiler;

    List< Statement > statements = Source::fromStream( std::cin ).parse( );
    llvm::Module * module = compiler.build( statements, argv[ 1 ] );

    module->print( llvm::outs( ), nullptr );

    return 0;
}
