#include "castel/ast/stmt/Return.hh"
#include "castel/engine/CodeGenerator.hh"

using namespace castel;
using namespace castel::engine;

void CodeGenerator::visit( ast::stmt::Return & astReturnStatement )
{
    if ( astReturnStatement.returnValue( ) ) {
        astReturnStatement.returnValue( )->accept( *this );
        mGenerationEngine.irBuilder( ).CreateRet( mValue.release( ) );
    } else {
        mGenerationEngine.irBuilder( ).CreateRetVoid( );
    }
}
