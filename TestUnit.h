#pragma once
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

class TestUnit
{
public:
	TestUnit();
	~TestUnit();
	static int RunTests();
};

