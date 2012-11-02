#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/builder/SetterGenerator.hh"

using namespace castel;
using builder::SetterGenerator;

void SetterGenerator::visit( ast::expr::Binary & astBinaryExpression )
{
    if ( ! astBinaryExpression.leftOperand( ) )
        throw std::runtime_error( "Missing left operand" );

    if ( ! astBinaryExpression.rightOperand( ) )
        throw std::runtime_error( "Missing right operand" );

    if ( astBinaryExpression.type( ) != ast::expr::Binary::Operator::Member )
        this->defaultAction( astBinaryExpression );

    llvm::Value * llvmInstance = builder::CodeGenerator( mContext, mScope ).expression( * ( astBinaryExpression.leftOperand( ) ) );
    llvm::Value * llvmName = builder::CodeGenerator( mContext, mScope ).expression( * ( astBinaryExpression.rightOperand( ) ) );
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_setProperty", llvmInstance, llvmName, mValue.release( ) ) );
}
