#include <iostream>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

int main ( int argc, char* argv[ ] )
{
    // informs test-listener about testresults
    CppUnit::TestResult testResult;

    // register listener for collecting the test-results
    CppUnit::TestResultCollector collectedResults;
    testResult.addListener( &collectedResults );

    // register listener for per-test progress output
    CppUnit::BriefTestProgressListener progress;
    testResult.addListener( &progress );

    // insert test-suite at test-runner by registry
    CppUnit::TestRunner testRunner;
    testRunner.addTest( CppUnit::TestFactoryRegistry::getRegistry( ).makeTest( ) );
    testRunner.run( testResult );

    // output results in compiler-format
    CppUnit::CompilerOutputter compilerOutputter( &collectedResults, std::cout );
    compilerOutputter.write( );

    // return 0 if tests were successful
    return collectedResults.wasSuccessful( ) ? 0 : 1;
}
