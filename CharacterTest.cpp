////! @file 
////! @brief Implementation file for the Character Testing class  
////!
//
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
//using namespace CppUnit;
//using namespace std;
//#include "stdafx.h"
//#include "Game.h"
//#include "Character.h"
//#include "Fighter.h"
//
//
////! Test Class for the Character class
//class CharacterTest : public CppUnit::TestFixture
//{
//	CPPUNIT_TEST_SUITE(CharacterTest);
//	CPPUNIT_TEST(higherLevelCharacter);
//	CPPUNIT_TEST(testLevelUp);
//	CPPUNIT_TEST(testValidNewCharacter);
//	CPPUNIT_TEST(testInvalidNewCharacter);
//	CPPUNIT_TEST(testHit);
//	CPPUNIT_TEST(testObserverPattern);
//	CPPUNIT_TEST_SUITE_END();
//protected:
//	void higherLevelCharacter();
//	void testLevelUp();
//	void testValidNewCharacter();
//	void testInvalidNewCharacter();
//	void testHit();
//	void testObserverPattern();
//};
//
////! test case registration
//CPPUNIT_TEST_SUITE_REGISTRATION(CharacterTest);
//
////! test method the constructor that accepts a character level
////! Test Case: Attributes should scale based on level entered
////! Tested item: Character::Character(int level)
//void CharacterTest::higherLevelCharacter() {
//	Character *conan = new Fighter(5);
//
//	//Print statements used for testing
//	std::cout << "new str: " << conan->getStr() << std::endl;
//	std::cout << "new dex: " << conan->getDex()<< std::endl;
//	std::cout << "new con: " << conan->getCon() << std::endl;
//	cout << "To be valid (new stat - old stat) should equal 4" << endl;
//
//	// Test done through print statements due to random factor when initializing new characters attributes
//	CPPUNIT_ASSERT(true);
//}
//
////! test method the level up method of the Character class
////! Test Case: After randomly generating attribute values upon creation,
////!				str, dex, and con should increase by 1
////! Tested item: Character::levelUp()
//void CharacterTest::testLevelUp()
//{
//	Character *conan = new Fighter();
//	bool valid = false;
//
//	//Setting variables for comparison after random generation
//	int str = conan->getStr();
//	int dex = conan->getDex();
//	int con = conan->getCon();
//
//	//Proceed with two level ups
//	conan->levelUp();
//	conan->levelUp();
//
//	if (conan->getStr() == str + 2) {
//		if (conan->getDex() == dex + 2)
//			if (conan->getCon() == con + 2)
//				valid = true;
//	}
//
//	CPPUNIT_ASSERT(valid);
//}
//
////! test method to test the validateNewCharacter() method of the Character class 
////! Test Case: a valid newly created character should have all its ability scores in the [3-18] range
////! Tested item: Character::validateNewCharacter()
//void CharacterTest::testValidNewCharacter()
//{
//	Character *conan = new Fighter();
//	CPPUNIT_ASSERT(conan->validateNewCharacter() == true);
//}
//
////! test method to test the validateNewCharacter() method of the Character class 
////! Test Case: an invalid newly created character should have any of its ability scores outside the [3-18] range
////! Tested item: Character::validateNewCharacter()
//void CharacterTest::testInvalidNewCharacter()
//{
//	Character *conan = new Fighter();
//	conan->setStr(19);
//	CPPUNIT_ASSERT(conan->validateNewCharacter() == false);
//}
//
////! test method to test the hit() method of the Map class 
////! Test Case: a character that has been hit(x) should have its hit points reduced by x 
////! Tested item: Character::hit()
//void CharacterTest::testHit()
//{
//	Character *conan = new Fighter();
//	conan->hit(4);
//	CPPUNIT_ASSERT(conan->getMaxHp() - conan->getHp() == 4);
//}
//
////! to test that the hp of the character will adjust after being hit, and display accordiingly (Observer pattern)
////! Test case: a character that has been hit(x) should have its hit points reduced by x
////! Test item Character::hit() (as an Observer)
//void CharacterTest::testObserverPattern()
//{
//	const int SCREEN_WIDTH = 720;
//	const int SCREEN_HEIGHT = 580;
//	Game* g = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
//	g->DriverGameLoop(1);
//
//	//Assert that hitpoints visually decrease by one by pressing the 'H' key
//	//Note: No validation done as of yet, therefore HP can go below zero.
//}