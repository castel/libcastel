#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Binary & astBinaryExpression )
{
    if ( ! astBinaryExpression.leftOperand( ) )
        throw std::runtime_error( "Missing left operand" );

    if ( ! astBinaryExpression.rightOperand( ) )
        throw std::runtime_error( "Missing right operand" );

    if ( astBinaryExpression.type( ) == ast::expr::Binary::Operator::Assignment ) {

        ast::expr::Variable * astVariable = dynamic_cast< ast::expr::Variable * >( astBinaryExpression.leftOperand( ) );

        if ( ! astVariable )
            throw std::runtime_error( "Invalid lvalue" );

        astBinaryExpression.rightOperand( )->accept( *this );
        mClosureStack.top( )->set( astVariable->name( ), mValue.get( ) );

    } else {

        astBinaryExpression.leftOperand( )->accept( * this );
        llvm::Value * llvmLeftOperand = mValue.release( );

        astBinaryExpression.rightOperand( )->accept( * this );
        llvm::Value * llvmRightOperand = mValue.release( );

        switch ( astBinaryExpression.type( ) ) {

            case ast::expr::Binary::Operator::Addition:
                mValue.reset( mContext.irBuilder().CreateCastelCall( "castel_additionOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Substraction:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_substractionOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Multiplication:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_multiplicationOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Division:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_divisionOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Modulo:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_moduloOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Lesser:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_lesserOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Greater:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_greaterOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::LesserOrEqual:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_lesserOrEqualOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::GreaterOrEqual:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_greaterOrEqualOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::Equal:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_equalOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::NotEqual:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_notEqualOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::AdditionAssignment:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_additionAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::SubstractionAssignment:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_substractionAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::MultiplicationAssignment:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_multiplicationAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::DivisionAssignment:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_divisionAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

            case ast::expr::Binary::Operator::ModuloAssignment:
                mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_moduloAssignmentOperator", llvmLeftOperand, llvmRightOperand ) );
            break;

        }

    }

}
