#include "ChestObserver.h"

#define CHEST_CAST dynamic_cast<ItemContainer*>(getSubject())
#define CHARACTER CHEST_CAST->getMap()->getCharacter()

ChestObserver::ChestObserver(Subject* subj) : Observer(subj)
{
}


ChestObserver::~ChestObserver()
{
}

//!see observer and related functions to update
void ChestObserver::update() {
	printChestDetails();
}

//!simple view function that prints a recognition that the program detects players level and can print out messages of chest opening
void ChestObserver::printChestDetails() {
	std::cout << "\nYou Open a Chest\n";
	std::cout << "This chest corresponds to a level " << CHARACTER->getLevel() << " Character !\n\n";

	std::cout << "YOU ARE NOW VIEWING THE CHEST\n";

	bool lookingAtChest = true;
	while (lookingAtChest) {
		if (CHARACTER->lastOpenedChest->getOpen()) { //last opened chest is a field that holds the chest aquired by checklook(dir)
			std::cout << "\nIt's Empty\n";
			std::cout << "You have no choice but to leave\n\n";
			lookingAtChest = false;
		}
		else {
			std::cout << "DO YOU OPEN IT ? (1 OR 0)\n";
			std::string response = "";
			cin >> response;
			if (response == "1") {

				std::cout << "THIS CHEST CONTAINS:\n" << CHARACTER->lastOpenedChest->getItem(0)->toString();
				std::cout << "Do you pick it up ? (1 or 0)";
				response;
				cin >> response;
				if (response == "1") {
					CHARACTER->lastOpenedChest->setOpen(true);
					CHARACTER->getInventory()->push_back(CHARACTER->lastOpenedChest->getItem(0));
				}

				lookingAtChest = false;

			}
			else {
				lookingAtChest = false;
			}
		}
	}
}