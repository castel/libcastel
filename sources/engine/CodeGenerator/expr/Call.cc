#include <stdexcept>
#include <vector>

#include <llvm/Value.h>

#include "castel/ast/expr/Call.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::expr::Call & call )
{
    /* Checks that the AST has defined a callee function */
    if ( ! call.callee( ) )
        throw std::runtime_error( "Missing callee" );

    /* Computes the function box which we'll need to inspect */
    call.callee( )->accept( *this );
    llvm::Value * box = mValue.release( );

    /* Computes arguments */
    std::vector< llvm::Value * > arguments;

    for ( auto & item : call.arguments( ) ) {

        if ( ! item.value( ) )
            throw std::runtime_error( "Missing expression" );

        item.value( )->accept( *this );
        arguments.push_back( mValue.release( ) );

    }

    /* Pseudo-returns the return value of the inner LLVM function call */
    mValue.reset( mLLVMHelpers.callFunctionBox( box, arguments ) );
}
