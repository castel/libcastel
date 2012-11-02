#include "castel/ast/stmt/Return.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::Return & astReturnStatement )
{
    if ( astReturnStatement.expression( ) ) {
        mContext.irBuilder( ).CreateRet( builder::CodeGenerator( mContext, mScope ).expression( * ( astReturnStatement.expression( ) ) ) );
    } else {
        mContext.irBuilder( ).CreateRet( mContext.irBuilder( ).CreateCastelCall( "castelUndefined_create" ) );
    }
}
