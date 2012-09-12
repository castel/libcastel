#include "castel/ast/stmt/Return.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::visit( ast::stmt::Return & astReturnStatement )
{
    if ( astReturnStatement.returnValue( ) ) {
        astReturnStatement.returnValue( )->accept( *this );
        mContext.irBuilder( ).CreateRet( mValue.release( ) );
    } else {
        mContext.irBuilder( ).CreateRet( mContext.irBuilder( ).CreateCastelCall( "castelUndefined_create" ) );
    }
}
