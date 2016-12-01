////! @file 
////! @brief File containing the Test Class and the Test Methods for the MapSaveBuilder
////!
//
//#include <iostream>
//#include <cppunit/TestCase.h>
//#include <cppunit/TestFixture.h>
//#include <cppunit/ui/text/TextTestRunner.h>
//#include <cppunit/extensions/HelperMacros.h>
//#include <cppunit/extensions/TestFactoryRegistry.h>
//#include <cppunit/TestResult.h>
//#include <cppunit/TestResultCollector.h>
//#include <cppunit/TestRunner.h>
//#include <cppunit/BriefTestProgressListener.h>
//#include <cppunit/CompilerOutputter.h>
//#include <cppunit/XmlOutputter.h>
//#include <cppunit/ui/text/TestRunner.h>
//#include "MapSaveBuilder.h"
//#include "MapDirector.h"
//using namespace CppUnit;
//using namespace std;
//
//
////! Test Class for the MapSaveBuilder class
////! It must be a subclass of CppUnit::TestFixture
////! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
////! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
//
////! Test Class for the LevelMapBuilder class contains main test method
//class TestMapSaveBuilder : public CppUnit::TestFixture
//{
//	CPPUNIT_TEST_SUITE(TestMapSaveBuilder);
//	CPPUNIT_TEST(testValidMonsters);
//	CPPUNIT_TEST(testValidTreasures);
//	CPPUNIT_TEST_SUITE_END();
//protected:
//	void testValidMonsters(void);
//	void testValidTreasures(void);
//};
//
////!Register for running the test
//CPPUNIT_TEST_SUITE_REGISTRATION(TestMapSaveBuilder);//most important
//
////! Tests the Builder pattern creation of a map from a saved file
////! This method tests whether or not the correct amount of monsters are created
////! A monster is denoted by an 'm' on the map. There are three 'm's so we expect 3 monsters to be created.
//void TestMapSaveBuilder::testValidMonsters(void)
//{
//	MapDirector mapDirector;
//	MapSaveBuilder* mapSaveBuilder = new MapSaveBuilder();
//	mapDirector.setMapBuilder(mapSaveBuilder);
//	mapDirector.constructMap("map.txt");
//	Map* map = mapSaveBuilder->getMap();
//	vector<Monster>* monsters = mapSaveBuilder->getMonsters();
//	// There are 3 'm's in the example.txt so we expect two monsters to be made
//	CPPUNIT_ASSERT(monsters->size() == 3);
//}
//
////! Tests the Builder pattern creation of a map from a saved file
////! Treasure is a container for items
////! This method tests whether or not the correct amount of treasures are created
////! A treasure is denoted by an 't' on the map. There are two 't's so we expect 2 treasures to be created.
//void TestMapSaveBuilder::testValidTreasures(void)
//{
//	MapDirector mapDirector;
//	MapSaveBuilder* mapSaveBuilder = new MapSaveBuilder();
//	mapDirector.setMapBuilder(mapSaveBuilder);
//	mapDirector.constructMap("map.txt");
//	Map* map = mapSaveBuilder->getMap();
//	vector<vector<Item>>* treasureList = mapSaveBuilder->getTreasure();
//	// There are 2 't's in the example.txt so we expect two treasures to be made
//	CPPUNIT_ASSERT(treasureList->size() == 2);
//}
//
//// Uncomment to run tests
///*
//int main(int ac, char **av)
//{
//	//--- Create the event manager and test controller
//	CPPUNIT_NS::TestResult controller;
//
//	//--- Add a listener that colllects test result
//	CPPUNIT_NS::TestResultCollector result;
//	controller.addListener(&result);
//
//	//--- Add a listener that print dots as test run.
//	CPPUNIT_NS::BriefTestProgressListener progress;
//	controller.addListener(&progress);
//
//	//--- Add the top suite to the test runner
//	CPPUNIT_NS::TestRunner runner;
//
//	runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
//	runner.run(controller);
//	
//
//
//	getchar();
//	return result.wasSuccessful() ? 0 : 1;
//}
//*/
//
