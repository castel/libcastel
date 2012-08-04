#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::expr::Binary & binaryExpression )
{
    if ( ! binaryExpression.left( ) )
        throw std::runtime_error( "Missing left-hand expression" );

    if ( ! binaryExpression.right( ) )
        throw std::runtime_error( "Missing right-hand expression" );

    switch ( binaryExpression.type( ) ) {

        case lexer::Lexeme::Type::Assign:

            {
                auto asVariable = dynamic_cast< ast::expr::Variable * >( binaryExpression.left( ) );

                if ( ! asVariable )
                    throw std::runtime_error( "Invalid lvalue" );

                binaryExpression.right( )->accept( *this );
                llvm::Value * value = mValue.release( );

                switch ( binaryExpression.type( ) ) {
                    default: break;

                    case lexer::Lexeme::Type::Assign:
                        llvm::Value * destination;
                        if ( asVariable )
                            mClosureStack.top( )->set( asVariable->name( ), value );
                    break;

                }

            }

        break;

        case lexer::Lexeme::Type::Add:
        case lexer::Lexeme::Type::Substract:
        case lexer::Lexeme::Type::Multiply:
        case lexer::Lexeme::Type::Divide:
        case lexer::Lexeme::Type::Modulo:

            {

                binaryExpression.left( )->accept( *this );
                llvm::Value * left = mLLVMHelpers.boxToDouble( mValue.release( ) );

                binaryExpression.right( )->accept( *this );
                llvm::Value * right = mLLVMHelpers.boxToDouble( mValue.release( ) );

                llvm::Value * result = nullptr;

                switch ( binaryExpression.type( ) ) {
                    default: break;

                    case lexer::Lexeme::Type::Add:
                        result = mGenerationEngine.irBuilder( ).CreateFAdd( left, right, "add" );
                    break;

                    case lexer::Lexeme::Type::Substract:
                        result = mGenerationEngine.irBuilder( ).CreateFSub( left, right, "sub" );
                    break;

                    case lexer::Lexeme::Type::Multiply:
                        result = mGenerationEngine.irBuilder( ).CreateFSub( left, right, "mul" );
                    break;

                    case lexer::Lexeme::Type::Divide:
                        result = mGenerationEngine.irBuilder( ).CreateFDiv( left, right, "div" );
                    break;

                    case lexer::Lexeme::Type::Modulo:
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
