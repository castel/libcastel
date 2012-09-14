#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Binary & astBinaryExpression )
{
    if ( ! astBinaryExpression.leftOperand( ) )
        throw std::runtime_error( "Missing left operand" );

    if ( ! astBinaryExpression.rightOperand( ) )
        throw std::runtime_error( "Missing right operand" );

    astBinaryExpression.leftOperand( )->accept( * this );
    llvm::Value * llvmLeftOperand = mValue.release( );

    astBinaryExpression.rightOperand( )->accept( * this );
    llvm::Value * llvmRightOperand = mValue.release( );

    if ( astBinaryExpression.type( ) == lexer::Lexeme::Type::Assignment ) {

        ast::expr::Variable * astVariable = dynamic_cast< ast::expr::Variable * >( astBinaryExpression.left( ) );

        if ( ! astVariable )
            throw std::runtime_error( "Invalid lvalue" );

        astBinaryExpression.right( )->accept( *this );
        mClosureStack.top( )->set( asVariable->name( ), mValue.get( ) );

    } else {

        switch ( astBinaryExpression.type( ) ) {

        case lexer::Lexeme::Type::Addition:
            mValue.reset( mContext.CreateCastelCall( "castel_additionOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Substraction:
            mValue.reset( mContext.CreateCastelCall( "castel_substractionOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Multiplication:
            mValue.reset( mContext.CreateCastelCall( "castel_multiplicationOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Division:
            mValue.reset( mContext.CreateCastelCall( "castel_divisionOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Modulo:
            mValue.reset( mContext.CreateCastelCall( "castel_moduloOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Lesser:
            mValue.reset( mContext.CreateCastelCall( "castel_lesserOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Greater:
            mValue.reset( mContext.CreateCastelCall( "castel_greaterOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::LesserOrEqual:
            mValue.reset( mContext.CreateCastelCall( "castel_lesserOrEqualOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::GreaterOrEqual:
            mValue.reset( mContext.CreateCastelCall( "castel_greaterOrEqualOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::Equal:
            mValue.reset( mContext.CreateCastelCall( "castel_equalOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::NotEqual:
            mValue.reset( mContext.CreateCastelCall( "castel_notEqualOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::AdditionAssignment:
            mValue.reset( mContext.CreateCastelCall( "castel_additionAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::SubstractionAssignment:
            mValue.reset( mContext.CreateCastelCall( "castel_substractionAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::MultiplicationAssignment:
            mValue.reset( mContext.CreateCastelCall( "castel_multiplicationAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::DivisionAssignment:
            mValue.reset( mContext.CreateCastelCall( "castel_divisionAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        case lexer::Lexeme::Type::ModuloAssignment:
            mValue.reset( mContext.CreateCastelCall( "castel_moduloAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        }

    }

    if ( 1 ) {

        case lexer::Lexeme::Type::Assign:

            {
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
