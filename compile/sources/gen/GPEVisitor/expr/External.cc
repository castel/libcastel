#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>

#include "castel/ast/expr/External.hh"
#include "castel/gen/helper/call.hh"
#include "castel/gen/helper/null.hh"
#include "castel/gen/helper/type.hh"
#include "castel/gen/GPEVisitor.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using gen::GPEVisitor;

void GPEVisitor::visit( ast::expr::External const & externalExpressionAst )
{
    mLastReturnedValue = gen::helper::call( mContext, mModule, mIRBuilder, "Castel_Function_create",
        mModule->getOrInsertFunction(
            externalExpressionAst.name( ),
            gen::helper::type< runtime::Box * ( runtime::Box ***, int, runtime::Box ** ) >( mContext ) ),
        llvm::ConstantInt::get( mContext, llvm::APInt( 32, 0 ) ),
        gen::helper::null< runtime::Box *** >( mContext )
    );
}
