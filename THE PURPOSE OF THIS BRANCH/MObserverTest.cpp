//! @file 
//! @brief Implementation file for the DiceTest class  
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

#include "Map.h"
#include "MapObserver.h"

using namespace CppUnit;

//! Test Class for the Dice class
class MObserverTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MObserverTest);
	//DECLAR TESTS WITH CPPUNIT_TEST(testDiceRollInputValidity); //test the lower bound of the returned value 

	CPPUNIT_TEST(testValidMapObserverSize);
	CPPUNIT_TEST(testSquareRecognition);

	CPPUNIT_TEST_SUITE_END();
protected:
//DO TEST METHODS
	void testValidMapObserverSize();
	void testSquareRecognition();
};

//! cppunit test cases registration
CPPUNIT_TEST_SUITE_REGISTRATION(MObserverTest);

//! test method for printMap() method of the Map Observer
//! Test Case: the the validity of output string.
//! Should result in a the area of the map.
void MObserverTest::testValidMapObserverSize() {
	//rows
	for (int i = 3; i < 15; i++) {
		//collumns
		for (int j = 3; j < 15; j++) {
			Map map(i, j);
			MapObserver mo(&map);
			Character character(&map);

			map.initializeMap();

			//get the number of rows and columns subtracting brackets and \n's
											   //all row's \n[] and the last \n
			int result = mo.printMap().length() - (	 i * 3             + 1);
			//std::cout << result << " " << mo.printMap() << "\n";

			CPPUNIT_ASSERT(result == i * j);

			map.deleteMap();
		}
	}
}

//! test method for printNotifications() method of the Map Observer
//! Test Case: the the validity of output string.
//! Should result in a valid string from a set of choices
void MObserverTest::testSquareRecognition() {
	//rows
	for (int i = 3; i < 5; i++) {
		//collumns
		for (int j = 3; j < 5; j++) {
			Map map(i, j);
			MapObserver mo(&map);
			Character character(&map);

			map.initializeMap();

			for (int n = 0; n < i - 3; n++) {
				for (int m = 0; m < j;m++) {

					char square = map.getMap()[n][m];
					map.setCurrentSquare(character.StandingOn(m, n));

					std::string result = mo.printNotifications();
					if (square == '#') {
						CPPUNIT_ASSERT(result == "YOU ARE OVER A TILE\n");
					}
					else if (square == 's') {
						CPPUNIT_ASSERT(result == "YOU ARE OVER AN ENTRANCE\n");
					}
					else if (square == 'e') {
						CPPUNIT_ASSERT(result == "YOU ARE OVER AN EXIT\n");
					}
					else if (square == 'O') {
						CPPUNIT_ASSERT(result == "YOU ARE STANDING ON SOMETHING YOU SHOULDN'T BE ON\n");
					}
					else if (square == '&') {
						CPPUNIT_ASSERT(result == "YOU ARE STANDING ON SOMETHING YOU SHOULDN'T BE ON\n");
					}
					else if (square == '^') {
						CPPUNIT_ASSERT(result == "YOU ARE STANDING ON SOMETHING YOU SHOULDN'T BE ON\n");
					}
				}
				map.deleteMap();
			}
		}
	}
}

// USE:::: CPPUNIT_ASSERT(result >= 1);
