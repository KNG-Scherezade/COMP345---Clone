#include "stdafx.h"
#include "TestUnit.h"


TestUnit::TestUnit()
{
}


TestUnit::~TestUnit()
{
}

int TestUnit::RunTests() {

	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the lsit of tests to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

	// Run the tests
	bool wasSuccessful = runner.run();

	getchar();

	// Return error code 1 if one of the tests failed.
	return wasSuccessful ? 0 : 1;
}
