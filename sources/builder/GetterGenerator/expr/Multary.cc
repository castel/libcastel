#include <iterator>
#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Multary.hh"
#include "castel/builder/GetterGenerator.hh"

using namespace castel;
using builder::GetterGenerator;

static std::map< ast::expr::Multary::Operator, char const * > const operatorsTable {

    std::make_pair( ast::expr::Multary::Operator::New, "castel_new" ),

    std::make_pair( ast::expr::Multary::Operator::Call, "castel_operatorCall" ),
    std::make_pair( ast::expr::Multary::Operator::Subscript, "castel_operatorSubscript" ),

};

void GetterGenerator::visit( ast::expr::Multary & astMultaryExpression )
{
    if ( ! astMultaryExpression.operands( ) )
        throw std::runtime_error( "Missing operands" );

    ast::Expression * astLeftMostOperand = astMultaryExpression.operands( );
    ast::Expression * astArguments = astLeftMostOperand->next( );

    llvm::Value * llvmLeftMostOperand = builder::GetterGenerator( mScope ).run( * astLeftMostOperand );

    llvm::Value * llvmArgCount = llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, std::distance( utils::begin( astArguments ), utils::end( astArguments ) ) ) );
    llvm::Value * llvmArguments = mContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( llvmArgCount );

    int argumentIndex = 0;
    for ( auto & astArgument : astArguments ) {

        llvm::Value * llvmArgTarget = mContext.irBuilder( ).CreateConstGEP1_64( llvmArguments, argumentIndex ++ );
        llvm::Value * llvmArgument = builder::GetterGenerator( mScope ).run( astArgument );

        mContext.irBuilder( ).CreateStore( llvmArgument, llvmArgTarget );

    }

    mLLVMValue = mContext.irBuilder( ).CreateCastelCall( operatorsTable.at( astMultaryExpression.type( ) ), llvmLeftMostOperand, llvmArgCount, llvmArguments );
}
