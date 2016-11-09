#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "MapObserver.h"
#include "Map.h"
#include "Chest.h"
#include "ChestObserver.h"

int main(int argc, char** argv) {


#define DRIVER
//#define TEST
#ifdef TEST

// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	getchar();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;

#endif //TEST

#ifdef DRIVER
	Map map(12, 12);
	Character character(&map);

	MapObserver mo1(&map);

	//play instructions
	std::cout << "\n& represents a chest,\n^ represents an open chest,\nO represents a pillar,\n# is empty\ne represents end point and s represents start point\n\n";
	std::cout << "\nWhen enter is pressed the program checks if a randomly generated map\nis solvable where s is always random and e is always random\nType e when over an entrance or exit to move to the next room" <<
		"\nIt likely will create a chest and a pillar, but that's not  garunteed\n\n\n";

	//initialization
	std::cout << "1) enter to init 12X12map for one map observer\n";
	getchar();
	map.initializeMap();

	std::cout << "\nInfinite Loop has been entered\n\n";
	while (true) {
		char direction;
		std::cout << "Enter A Direction To Move of \"l, r, u or d\" or enter \"e\" to interact:\n";
		std::cin >> direction;
		if (direction == 'e' || direction == 'E') {
			if (map.getCurrentSquare() == 1) {
				getchar();
				//reset map

				//MUST BE CALLED BEFORE CHESTS ARE CREATED
				character.setLevel(character.getLevel() + 1);
				map.initializeMap();

				std::cout << "You Move to an new Room AND GAIN A LEVEL\n";
				continue;
			}
			else if (map.getCurrentSquare() == -1) {
				getchar();

				//MUST BE CALLED BEFORE CHESTS ARE CREATED
				character.setLevel(character.getLevel() - 1);
				map.initializeMap();

				std::cout << "You Move to an old Room AND LOSE A LEVEL\n";
				continue;
			}

			std::cout << "Enter A Direction To Interact of \"l, r, u or d\". U and D allow diagonals:\n";
			std::cin >> direction;
			int msg = character.checkLook(direction);
		}
		else {
			//move character in direction
			character.checkMove(direction);
		}
	}//gameloop continues
	return 0;
#endif // Driver
}