#include <iterator>
#include <stdexcept>

#include <llvm/ADT/APInt.h>
#include <llvm/Constants.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Call.hh"
#include "castel/builder/CodeGenerator.hh"
#include "castel/utils/Linked.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::expr::Call & astCallExpression )
{
    /* Checks that the AST has defined a callee function */
    if ( ! astCallExpression.callee( ) )
        throw std::runtime_error( "Missing callee" );

    /* Computes the function box which we'll need to inspect */
    astCallExpression.callee( )->accept( *this );
    llvm::Value * box = mValue.release( );

    /* Computes arguments */
    llvm::Value * argc = llvm::ConstantInt::get( mContext.llvmContext( ), llvm::APInt( 32, std::distance( utils::begin( astCallExpression.arguments( ) ), utils::end( astCallExpression.arguments( ) ) ) ) );
    llvm::Value * argv = mContext.irBuilder( ).CreateCastelAllocate< runtime::Box * >( argc );

    int argumentIndex = 0;
    for ( auto & item : astCallExpression.arguments( ) ) {

        if ( ! item.value( ) )
            throw std::runtime_error( "Missing expression" );

        item.value( )->accept( *this );

        llvm::Value * argvTarget = mContext.irBuilder( ).CreateConstGEP1_64( argv, argumentIndex );
        mContext.irBuilder( ).CreateStore( mValue.release( ), argvTarget );

    }

    /* Pseudo-returns the return value of the inner LLVM function call */
    mValue.reset( mContext.irBuilder( ).CreateCastelCall( "castel_callOperator", box, argc, argv ) );
}
