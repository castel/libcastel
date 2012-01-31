#include <memory>

#include <cppunit/extensions/HelperMacros.h>

#include "p9/ast/StatementList.hh"
#include "p9/ast/Token.hh"

#include "libp9tests.hh"

using namespace p9;

void libp9tests::valid( void )
{
	initParser( &fromFile, "./assets/valid.p9" );
	
	std::auto_ptr< ast::Token > root( parser->exec( ) );
	
	CPPUNIT_ASSERT( root.get( ) );
	
	int statementCount = static_cast< ast::StatementList * >( root.get( ) )->size( );
	
	CPPUNIT_ASSERT_EQUAL( 1, statementCount );
}
