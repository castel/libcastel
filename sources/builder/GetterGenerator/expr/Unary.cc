#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Unary.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

static std::map< ast::expr::Unary::Operator, char const * > const operatorsTable {

    std::make_pair( ast::expr::Unary::Operator::NumericPreIncrementation, "castel_operatorNumericPreIncrementation" ),
    std::make_pair( ast::expr::Unary::Operator::NumericPreDecrementation, "castel_operatorNumericPreDecrementation" ),

    std::make_pair( ast::expr::Unary::Operator::NumericPostIncrementation, "castel_operatorNumericPostIncrementation" ),
    std::make_pair( ast::expr::Unary::Operator::NumericPostDecrementation, "castel_operatorNumericPostDecrementation" ),

    std::make_pair( ast::expr::Unary::Operator::NumericPlus, "castel_operatorNumericPlus" ),
    std::make_pair( ast::expr::Unary::Operator::NumericMinus, "castel_operatorNumericMinus" ),

    std::make_pair( ast::expr::Unary::Operator::BinaryNot, "castel_operatorBinaryNot" ),

};

void GetterGenerator::visit( ast::expr::Unary & astUnaryExpression )
{
    ast::Expression * astOperand = astUnaryExpression.operand( );

    if ( astOperand == nullptr )
        throw std::runtime_error( "Missing operand" );

    llvm::Value * llvmOperand = builder::GetterGenerator( mScope ).run( * astOperand );
    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( operatorsTable.at( astUnaryExpression.type( ) ), llvmOperand );
}
