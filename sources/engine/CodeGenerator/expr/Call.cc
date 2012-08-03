#include <stdexcept>
#include <vector>

#include <llvm/Value.h>

#include "p9/ast/expr/Call.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

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
