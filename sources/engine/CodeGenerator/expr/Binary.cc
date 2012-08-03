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

    switch ( binaryExpression.type( ) ) {

        case lexer::TAssign:

            {
                auto asVariable = dynamic_cast< ast::expr::Variable * >( binaryExpression.left( ) );

                if ( ! asVariable )
                    throw std::runtime_error( "Invalid lvalue" );

                binaryExpression.right( )->accept( *this );
                llvm::Value * value = mValue.release( );

                switch ( binaryExpression.type( ) ) {
                    default: break;

                    case lexer::TAssign:
                        llvm::Value * destination;
                        if ( asVariable )
                            mClosureStack.top( )->set( asVariable->name( ), value );
                    break;

                }

            }

        break;

        case lexer::TAdd:
        case lexer::TSubstract:
        case lexer::TMultiply:
        case lexer::TDivide:
        case lexer::TModulo:

            {

                binaryExpression.left( )->accept( *this );
                llvm::Value * left = mLLVMHelpers.boxToDouble( mValue.release( ) );

                binaryExpression.right( )->accept( *this );
                llvm::Value * right = mLLVMHelpers.boxToDouble( mValue.release( ) );

                llvm::Value * result = nullptr;

                switch ( binaryExpression.type( ) ) {
                    default: break;

                    case lexer::TAdd:
                        result = mGenerationEngine.irBuilder( ).CreateFAdd( left, right, "add" );
                    break;

                    case lexer::TSubstract:
                        result = mGenerationEngine.irBuilder( ).CreateFSub( left, right, "sub" );
                    break;

                    case lexer::TMultiply:
                        result = mGenerationEngine.irBuilder( ).CreateFSub( left, right, "mul" );
                    break;

                    case lexer::TDivide:
                        result = mGenerationEngine.irBuilder( ).CreateFDiv( left, right, "div" );
                    break;

                    case lexer::TModulo:
                        throw std::runtime_error( "Not implemented" );
                    break;

                }

                mValue.reset( mLLVMHelpers.doubleToBox( result ) );

            }

        break;

        default:
            throw std::runtime_error( "Invalid token type" );
        break;

    }

}
