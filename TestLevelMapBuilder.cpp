//! @file 
//! @brief File containing the Test Class and the Test Methods for the LevelMapBuilder
//!

#include <iostream>
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
#include <cppunit/ui/text/TestRunner.h>
#include "LevelMapBuilder.h"
#include "MapDirector.h"
#include "Equipment.h"
using namespace CppUnit;
using namespace std;


//! Test Class for the LevelMapBuilder class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.

//! Test Class for the LevelMapBuilder class
class TestLevelMapBuilder : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestLevelMapBuilder);
	CPPUNIT_TEST(testValidMonstersLMB);
	CPPUNIT_TEST(testValidTreasuresLMB);
	CPPUNIT_TEST(testValidMonsterLevel);
	CPPUNIT_TEST(testValidTreasureLevel);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidMonstersLMB(void);
	void testValidTreasuresLMB(void);
	void testValidMonsterLevel(void);
	void testValidTreasureLevel(void);
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestLevelMapBuilder);//most important

//! Tests the Builder pattern creation of a map from a saved file using the LevelMapBuilder
//! This method tests whether or not the correct amount of monsters are created
//! A monster is denoted by an 'm' on the map. There are three 'm's so we expect 3 monsters to be created.
void TestLevelMapBuilder::testValidMonstersLMB(void)
{
	MapDirector mapDirector;
	LevelMapBuilder* lmb = new LevelMapBuilder(5);
	mapDirector.setMapBuilder(lmb);
	mapDirector.constructMap("map.txt");
	Map* map = lmb->getMap();
	vector<Monster>* monsters = lmb->getMonsters();
	// There are 3 'm's in the example.txt so we expect two monsters to be made
	CPPUNIT_ASSERT(monsters->size() == 3);
}

//! Tests the Builder pattern creation of a map from a saved file using the LevelMapBuilder
//! Treasure is a container for items
//! This method tests whether or not the correct amount of treasures are created
//! A treasure is denoted by an 't' on the map. There are two 't's so we expect 2 treasures to be created.
void TestLevelMapBuilder::testValidTreasuresLMB(void)
{
	MapDirector mapDirector;
	LevelMapBuilder* lmb = new LevelMapBuilder(5);
	mapDirector.setMapBuilder(lmb);
	mapDirector.constructMap("map.txt");
	Map* map = lmb->getMap();
	vector<vector<Item>>* treasureList = lmb->getTreasure();
	// There are 2 't's in the example.txt so we expect two treasures to be made
	CPPUNIT_ASSERT(treasureList->size() == 2);
}

//! Tests if the monster's level is appropriate 
//! Each monster's level should be 5 because that is the level set for the map
void TestLevelMapBuilder::testValidMonsterLevel(void)
{
	bool valid = true;
	MapDirector mapDirector;
	LevelMapBuilder* lmb = new LevelMapBuilder(5);
	mapDirector.setMapBuilder(lmb);
	mapDirector.constructMap("map.txt");
	Map* map = lmb->getMap();
	vector<Monster>* monsters = lmb->getMonsters();
	for each (Monster monster in *monsters)
	{
		if (monster.getLevel() != 5)
			valid = false;
	}
	// Assert that each monster is level 5
	CPPUNIT_ASSERT(valid == true);
}


//! Tests if the treasure's level is appropriate 
//! Each treasure's level should be 5 because that is the level set for the map
void TestLevelMapBuilder::testValidTreasureLevel(void)
{
	bool valid = true;
	MapDirector mapDirector;
	LevelMapBuilder* lmb = new LevelMapBuilder(5);
	mapDirector.setMapBuilder(lmb);
	mapDirector.constructMap("map.txt");
	Map* map = lmb->getMap();
	// List containing treasures
	vector<vector<Item>>* treasureList = lmb->getTreasure();
	for each (vector<Item> itemVec in *treasureList)
	{
		// List containing items
		for each (Item item in itemVec)
		{
			if (static_cast<Equipment&>(item).getLevel() != 5)
				valid = false;
		}
	}
	// Assert that each item in the treasure is level 5
	CPPUNIT_ASSERT(valid == true);
}

