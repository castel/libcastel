#include <iterator>
#include <stdexcept>

#include <llvm/Value.h>

#include "castel/ast/expr/Multary.hh"
#include "castel/ast/tools/Linked.hh"
#include "castel/gen/helper/allocate.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/i32.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

#define OPERATOR( X, Y ) std::make_pair( ast::expr::Multary::Operator::X, Y )
static std::map< ast::expr::Multary::Operator, char const * > const operatorsTable {

    OPERATOR( Subscript, "Castel_Operator_subscript" ),
    OPERATOR( Call, "Castel_Operator_call" ),
    OPERATOR( New, "Castel_Operator_new" ),
    OPERATOR( Require, "Castel_Operator_require" )

};

void GPEVisitor::visit( ast::expr::Multary & multaryExpressionAst )
{
    ast::Expression * leftMostOperandAst = multaryExpressionAst.operands( );

    if ( leftMostOperandAst == nullptr )
        throw std::runtime_error( "Missing operands" );

    ast::Expression * restAst = leftMostOperandAst->next( );

    llvm::Value * leftMostOperand = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * leftMostOperandAst );

    llvm::Value * argc = gen::helper::i32( mContext, std::distance( ast::tools::begin( restAst ), ast::tools::end( restAst ) ) );
    llvm::Value * argv = gen::helper::allocate< runtime::Box * >( mContext, mModule, mIRBuilder, argc );

    int argumentIndex = 0;
    for ( auto & argumentAst : restAst ) {
        mIRBuilder.CreateStore(
            gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( argumentAst ),
            mIRBuilder.CreateConstGEP1_64( argv, argumentIndex ++ )
        );
    }

    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, operatorsTable.at( multaryExpressionAst.type( ) ), leftMostOperand, argc, argv );
}
