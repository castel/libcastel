#include "castel/ast/expr/literal/Dict.hh"
#include "castel/gen/helper/allocate.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/i32.hh"
#include "castel/gen/helper/string.hh"
#include "castel/gen/GPEVisitor.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::literal::Dict & dictLiteralAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Dict_create" );

    for ( auto const & item : dictLiteralAst.items( ) ) {

        llvm::Value * string = gen::helper::string( mIRBuilder, item.name( ) );
        llvm::Value * box = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_String_create", string );
        llvm::Value * key = gen::helper::allocate< runtime::Box * >( mContext, mModule, mIRBuilder, 1 );
        mIRBuilder.CreateStore( box, key );

        llvm::Value * value = gen::GPEVisitor( mContext, mModule, mIRBuilder, mScope ).run( * ( item.value( ) ) );

        gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Dict_set", mLastReturnedValue, gen::helper::i32( mContext, 1 ), key, value );

    }
}
