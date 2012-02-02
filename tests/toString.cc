#include <cppunit/extensions/HelperMacros.h>

#include "p9/ast/Token.hh"
#include "p9/parser/Exception.hh"

#include "libp9tests.hh"

using namespace p9;

void libp9tests::toString( void )
{
	initParser( &fromFile, "./assets/full.p9" );
	
	std::auto_ptr< ast::Token > root( parser->exec( ) );
	
	std::string code1 = root->toString( );
	
	initParser( &fromString, code1 );
	
	root.reset( parser->exec( ) );
	
	std::string code2 = root->toString( );
	
	CPPUNIT_ASSERT_EQUAL( code2, code1 );
}
