#include <cppunit/extensions/HelperMacros.h>

#include "p9/ast/Token.hh"
#include "p9/parser/Exception.hh"

#include "libp9tests.hh"

using namespace p9;

void libp9tests::parseError( void )
{
	initParser( &fromString, "+" );
	
	CPPUNIT_ASSERT_THROW( delete parser->exec( ), parser::Exception );
}
