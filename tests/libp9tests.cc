#include <fstream>
#include <sstream>
#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "p9/lexer/Lexer.hh"
#include "p9/parser/Parser.hh"

#include "libp9tests.hh"

CPPUNIT_TEST_SUITE_REGISTRATION( libp9tests );

void libp9tests::setUp( void )
{
	source = 0;
	lexer = 0;
	parser = 0;
}

void libp9tests::tearDown( void )
{
	delete parser;
	parser = 0;
	
	delete lexer;
	lexer = 0;
	
	delete source;
	source = 0;
}

void libp9tests::initSource( Method method, std::string const & data )
{
	delete source;
	source = new std::string( method( data ) );
}

void libp9tests::initLexer( Method method, std::string const & data )
{
	initSource( method, data );
	
	delete lexer;
	lexer = new p9::lexer::Lexer( source->c_str( ), source->size( ) );
}

void libp9tests::initParser( Method method, std::string const & data )
{
	initLexer( method, data );
	
	delete parser;
	parser = new p9::parser::Parser( * lexer );
}

std::string libp9tests::fromString( std::string const & string )
{
	return string;
}

std::string libp9tests::fromFile( std::string const & file )
{
	std::ifstream fstream( file.c_str( ), std::ios_base::binary | std::ios_base::in );
	
	std::stringstream sstream;
	sstream << fstream.rdbuf( );
	
	return sstream.str( );
}
