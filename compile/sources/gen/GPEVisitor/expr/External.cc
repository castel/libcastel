#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Type.h>

#include "castel/ast/expr/External.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/null.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::External & externalExpressionAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "castelFunction_create",
        mModule->getOrInsertFunction(
            externalExpressionAst.rawName( ),
            gen::helper::type< runtime::Box * ( runtime::Box ***, int, runtime::Box ** ) >( mContext ) ),
        llvm::ConstantInt::get( mContext, llvm::APInt( 32, 0 ) ),
        gen::helper::null< runtime::Box *** >( mContext )
    );
}
