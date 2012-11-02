#if 0

#include <stdexcept>

#include "castel/ast/expr/New.hh"
#include "castel/builder/CodeGenerator.hh"

void CodeGenerator::visit( ast::expr::New & astNewExpression )
{
    if ( ! astNewExpression.constructor( ) )
        throw std::runtime_error( "Missing constructor" );

    astNewExpression.constructor( )->accept( * this );
    mLLVMValue.reset( mContext.irBuilder( ).CreateCastelCall( "castelClass_instanciate", mLLVMValue.release( ) ) );
}

#endif
