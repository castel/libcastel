#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Unary.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Unary & astUnaryExpression )
{
    if ( ! astUnaryExpression.operand( ) )
        throw std::runtime_error( "Missing operand" );

    astUnaryExpression.operand( )->accept( * this );
    llvm::Value * llvmOperand = mValue.release( );

    switch ( astUnaryExpression.type( ) ) {

        case ast::expr::Unary::Operator::Positive:
           mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_positiveOperator", llvmOperand ) );
        break;

        case ast::expr::Unary::Operator::Negative:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_negativeOperator", llvmOperand ) );
        break;

        case ast::expr::Unary::Operator::PreIncrementation:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_preIncrementationOperator", llvmOperand ) );
        break;

        case ast::expr::Unary::Operator::PostIncrementation:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_postIncrementationOperator", llvmOperand ) );
        break;

        case ast::expr::Unary::Operator::PreDecrementation:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_preDecrementationOperator", llvmOperand ) );
        break;

        case ast::expr::Unary::Operator::PostDecrementation:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_postDecrementationOperator", llvmOperand ) );
        break;

    }
}
