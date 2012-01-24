#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class libp9tests : public CppUnit::TestFixture {
	
	CPPUNIT_TEST_SUITE( libp9tests );
	#define TEST( x ) CPPUNIT_TEST( x )
	#include "tests.x"
	#undef TEST
	CPPUNIT_TEST_SUITE_END( );
	
public:
	
	void setUp( void );
	
	void tearDown( void );
	
public:
	
	#define TEST( x ) void x( void );
	#include "tests.x"
	#undef TEST
	
};
