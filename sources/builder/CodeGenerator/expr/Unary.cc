#include <stdexcept>

#include <llvm/Value.hh>

#include "castel/ast/expr/Unary.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/lexer/Lexeme.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Unary & astUnaryExpression )
{
    if ( ! astUnaryExpression.operand( ) )
        throw std::runtime_error( "Missing operand" );

    astUnaryExpression.operand( )->accept( * this );
    llvm::Value * llvmOperand = mValue.release( );

    switch ( astUnaryExpression.type( ) ) {

    case lexer::Lexeme::Type::Positive:
        mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_positiveOperator", llvmOperand ) );
        break;

    case lexer::Lexeme::Type::Negative:
        mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_negativeOperator", llvmOperand ) );
        break;

    case lexer::Lexeme::Type::PreIncrementation:
        mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_preIncrementationOperator", llvmOperand ) );
        break;

    case lexer::Lexeme::Type::PostIncrementation:
        mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_postIncrementationOperator", llvmOperand ) );
        break;

    case lexer::Lexeme::Type::PreDecrementation:
        mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_preDecrementationOperator", llvmOperand ) );
        break;

    case lexer::Lexeme::Type::PostDecrementation:
        mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_postDecrementationOperator", llvmOperand ) );
        break;

    }
}
