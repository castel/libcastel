#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

int main ( int argc, char* argv[ ] )
{
	// informs test-listener about testresults
	CppUnit::TestResult testresult;

	// register listener for collecting the test-results
	CppUnit::TestResultCollector collectedresults;
	testresult.addListener( &collectedresults );

	// register listener for per-test progress output
	CppUnit::BriefTestProgressListener progress;
	testresult.addListener( &progress );

	// insert test-suite at test-runner by registry
	CppUnit::TestRunner testrunner;
	testrunner.addTest( CppUnit::TestFactoryRegistry::getRegistry( ).makeTest( ) );
	testrunner.run( testresult );

	// output results in compiler-format
	CppUnit::CompilerOutputter compileroutputter( &collectedresults, std::cerr );
	compileroutputter.write( );

	// return 0 if tests were successful
	return collectedresults.wasSuccessful( ) ? 0 : 1;
}
