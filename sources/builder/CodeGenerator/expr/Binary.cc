#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

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
                llvm::Value * leftOperand = mValue.release( );

                binaryExpression.right( )->accept( *this );
                llvm::Value * rightOperand = mValue.release( );

                llvm::Value * result = nullptr;

                switch ( binaryExpression.type( ) ) {
                    default: break;

                    case lexer::Lexeme::Type::Add:
                        result = mContext.irBuilder( ).CreateCastelCall( "castel_additionOperator", leftOperand, rightOperand );
                    break;

                    case lexer::Lexeme::Type::Substract:
                        result = mContext.irBuilder( ).CreateCastelCall( "castel_substractionOperator", leftOperand, rightOperand );
                    break;

                    case lexer::Lexeme::Type::Multiply:
                        result = mContext.irBuilder( ).CreateCastelCall( "castel_multiplicationOperator", leftOperand, rightOperand );
                    break;

                    case lexer::Lexeme::Type::Divide:
                        result = mContext.irBuilder( ).CreateCastelCall( "castel_divisionOperator", leftOperand, rightOperand );
                    break;

                    case lexer::Lexeme::Type::Modulo:
                        result = mContext.irBuilder( ).CreateCastelCall( "castel_moduloOperator", leftOperand, rightOperand );
                    break;

                }

                mValue.reset( result );

            }

        break;

        default:
            throw std::runtime_error( "Invalid token type" );
        break;

    }

}
