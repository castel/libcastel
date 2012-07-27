#include <stdexcept>
#include <vector>

#include <llvm/Value.h>

#include "p9/ast/expr/Call.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Call & call )
{
    if ( ! call.callee( ) )
        throw std::runtime_error( "Missing callee" );

    llvm::BasicBlock * basicBlock = mGenerationEngine.builder( ).GetInsertBlock( );
    call.callee( )->accept( *this );
    llvm::Value * callee = mValue.release( );
    mGenerationEngine.builder( ).SetInsertPoint( basicBlock );

    std::vector< llvm::Value * > arguments;
    for ( auto & item : call.arguments( ) ) {
        if ( ! item.value( ) )
            throw std::runtime_error( "Missing expression" );
        item.value( )->accept( *this );
        arguments.push_back( mValue.release( ) );
    }

    mValue.reset( mGenerationEngine.builder( ).CreateCall( callee, arguments ) );
}
