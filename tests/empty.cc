#include <fstream>
#include <memory>

#include <cppunit/extensions/HelperMacros.h>

#include "p9/lexer/Lexer.hh"
#include "p9/parser/Parser.hh"
#include "p9/ast/Token.hh"
#include "p9/ast/StatementList.hh"

#include "libp9tests.hh"

using namespace p9;

void libp9tests::empty( void )
{
	initParser( &fromString, "" );
	
	std::auto_ptr< ast::Token > root( parser->exec( ) );
	
	CPPUNIT_ASSERT( root.get( ) );
	
	int statementCount = static_cast< ast::StatementList * >( root.get( ) )->size( );
	
	CPPUNIT_ASSERT_EQUAL( 0, statementCount );
}
