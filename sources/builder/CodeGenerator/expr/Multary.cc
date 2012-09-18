#include <iterator>
#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Multary.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Multary & astMultaryExpression )
{
    if ( ! astMultaryExpression.operands( ) )
        throw std::runtime_error( "Missing operands" );

    ast::Expression * leftMostOperand = astMultaryExpression.operands( );
    ast::Expression * arguments = leftMostOperand->next( );

    leftMostOperand->accept( * this );
    llvm::Value * llvmLeftMostOperand = mValue.release( );

    llvm::Value * llvmArgCount = llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, std::distance( utils::begin( arguments ), utils::end( arguments ) ) ) );
    llvm::Value * llvmArguments = mContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( llvmArgCount );

    int argumentIndex = 0;
    for ( auto & argument : arguments ) {

        argument.accept( * this );

        llvm::Value * llvmArgTarget = mContext.irBuilder( ).CreateConstGEP1_64( llvmArguments, argumentIndex ++ );
        mContext.irBuilder( ).CreateStore( mValue.release( ), llvmArgTarget );

    }

    switch ( astMultaryExpression.type( ) ) {

        case ast::expr::Multary::Operator::Call:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_callOperator", llvmLeftMostOperand, llvmArgCount, llvmArguments ) );
        break;

        case ast::expr::Multary::Operator::Subscript:
            mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_subscriptOperator", llvmLeftMostOperand, llvmArgCount, llvmArguments ) );
        break;

    }
}
