//! @file 
//! @brief Implementation file for the CampaignTest class  
//!
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "Campaign.h"
using namespace CppUnit;

//! Test Class for the Campaign class
class CampaignTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CampaignTest);

	// Tests I created.
	CPPUNIT_TEST(testAddMap);
	CPPUNIT_TEST(testRemoveMap);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	// Tests I created.
	void testAddMap();
	void testRemoveMap();
private:
	Map *map;
	Campaign *campaign;
};

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(CampaignTest);

//! method called before every test case in this test class
void CampaignTest::setUp()
{
	// Create a map with 5 rows and 5 columns
	map = new Map(5, 5);
	campaign = new Campaign();
}

//! method called after every test case in this test class
void CampaignTest::tearDown()
{
	delete map;
	delete campaign;
}

//! test method to test the addMap method of the Campaign class 
//! Test Case: the returned value should be 1 if the map is added correctly
//! Tested item: Campaign::addMap()
void CampaignTest::testAddMap()
{
	cout << "\n\nTesting testAddMap: ";
	campaign->addMap(map);

	// Should be a map in the campaign now
	CPPUNIT_ASSERT(1 == campaign->getMapsInCampaign());
}

//! test method to test the removeMap method of the Campaign class 
//! Test Case: the returned value should be 0 if the map that is added is immediately removed
//! Tested item: Campaign::removeMap()
void CampaignTest::testRemoveMap()
{
	cout << "\n\nTesting testRemoveMap: ";
	
	// Created to avoid the program from crashing due to the tear down
	Map* map2 = new Map(map);
	campaign->addMap(map2);
	campaign->removeMap(map2);

	// Should be a map in the campaign now
	CPPUNIT_ASSERT(0 == campaign->getMapsInCampaign());
}