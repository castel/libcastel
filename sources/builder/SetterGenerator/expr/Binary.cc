#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/builder/GetterGenerator.hh"
#include "castel/builder/SetterGenerator.hh"

using namespace castel;
using builder::SetterGenerator;

void SetterGenerator::visit( ast::expr::Binary & astBinaryExpression )
{
    ast::Expression * astLeftOperand = astBinaryExpression.leftOperand( );
    ast::Expression * astRightOperand = astBinaryExpression.rightOperand( );

    if ( astLeftOperand == nullptr && astRightOperand == nullptr )
        throw std::runtime_error( "Both operands missing" );

    if ( astBinaryExpression.leftOperand( ) == nullptr )
        throw std::runtime_error( "Missing left operand" );

    if ( astBinaryExpression.rightOperand( ) == nullptr )
        throw std::runtime_error( "Missing right operand" );

    if ( astBinaryExpression.type( ) != ast::expr::Binary::Operator::Member )
        this->defaultAction( astBinaryExpression );

    llvm::Value * llvmInstance = builder::GetterGenerator( mScope ).run( * ( astBinaryExpression.leftOperand( ) ) );
    llvm::Value * llvmName = builder::GetterGenerator( mScope ).run( * ( astBinaryExpression.rightOperand( ) ) );
    mContext.irBuilder( ).CreateCastelCall( "castel_setProperty", llvmInstance, llvmName, mLLVMValue );
}
