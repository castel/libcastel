#pragma once

#include "LibP9Tests.hh"

class P9Tests : public LibP9Tests
{

    CPPUNIT_TEST_SUITE( P9Tests );
    #define TEST( x ) CPPUNIT_TEST( x )
    #include "build/generated/testsList"
    #undef TEST
    CPPUNIT_TEST_SUITE_END( );

public:

    #define TEST( x ) void x( void );
    #include "build/generated/testsList"
    #undef TEST

};
