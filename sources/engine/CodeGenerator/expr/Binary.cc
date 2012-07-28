#include <stdexcept>

#include <llvm/Value.h>

#include "p9/ast/expr/Binary.hh"
#include "p9/lexer/Token.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Binary & binaryExpression )
{
    if ( ! binaryExpression.left( ) )
        throw std::runtime_error( "Missing left-hand expression" );

    if ( ! binaryExpression.right( ) )
        throw std::runtime_error( "Missing right-hand expression" );

    binaryExpression.left( )->accept( *this );
    llvm::Value * left = mLLVMHelpers.doubleValue( mValue.release( ) );

    binaryExpression.right( )->accept( *this );
    llvm::Value * right = mLLVMHelpers.doubleValue( mValue.release( ) );

    llvm::Value * result = nullptr;

    switch ( binaryExpression.type( ) ) {

        case lexer::TAdd:
            result = mGenerationEngine.builder( ).CreateFAdd( left, right, "add" );
        break;

        case lexer::TSubstract:
            result = mGenerationEngine.builder( ).CreateFSub( left, right, "sub" );
        break;

        case lexer::TMultiply:
            result = mGenerationEngine.builder( ).CreateFSub( left, right, "mul" );
        break;

        case lexer::TDivide:
            result = mGenerationEngine.builder( ).CreateFDiv( left, right, "div" );
        break;

        case lexer::TModulo:
        break;

        default:
            throw std::runtime_error( "Invalid token type" );
        break;

    }

    mValue.reset( mLLVMHelpers.boxDouble( result ) );

}
