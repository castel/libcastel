#include "p9/ast/stmt/Return.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::stmt::Return & astReturnStatement )
{
    if ( astReturnStatement.returnValue( ) ) {
        astReturnStatement.returnValue( )->accept( *this );
        mGenerationEngine.builder( ).CreateRet( mValue.release( ) );
    } else {
        mGenerationEngine.builder( ).CreateRetVoid( );
    }
}
