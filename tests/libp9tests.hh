#pragma once

#include <string>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "p9/lexer/Lexer.hh"
#include "p9/parser/Parser.hh"

class libp9tests : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( libp9tests );
	#define TEST( x ) CPPUNIT_TEST( x )
	#include "tests.x"
	#undef TEST
	CPPUNIT_TEST_SUITE_END( );
	
public:
	
	typedef std::string (*Method)( std::string const & );
	
public:
	
	void setUp( void );
	
	void tearDown( void );
	
public:
	
	void initSource( Method method, std::string const & data );
	
	void initLexer( Method method, std::string const & data );
	
	void initParser( Method method, std::string const & data );
	
protected:
	
	static std::string fromString( std::string const & string );
	
	static std::string fromFile( std::string const & file );
	
public:
	
	#define TEST( x ) void x( void );
	#include "tests.x"
	#undef TEST
	
private:
	
	std::string * source;
	
	p9::lexer::Lexer * lexer;
	
	p9::parser::Parser * parser;
	
};
