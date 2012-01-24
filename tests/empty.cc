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
	std::ifstream ifstream( "./assets/empty.p9" );
	
	std::stringstream stringstream;
	stringstream<< ifstream.rdbuf( );
	std::string buffer = stringstream.str( );
	
	lexer::Lexer lexer( buffer.c_str( ), buffer.length( ) );
	parser::Parser parser( lexer );
	
	std::auto_ptr< ast::Token > root( parser.exec( ) );
	
	CPPUNIT_ASSERT( root.get( ) );
	CPPUNIT_ASSERT_EQUAL( static_cast< ast::StatementList * >( root.get( ) )->size( ), static_cast< unsigned int >( 0 ) );
}
