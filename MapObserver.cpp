#include "MapObserver.h"
#define MAP_CAST dynamic_cast<Map*>(getSubject())
#define CHEST_OPEN MAP_CAST->getChestAtPosition(j, i)->getOpen()

MapObserver::MapObserver(Subject* subj) : Observer(subj)
{//does attatch in superclass
}


MapObserver::~MapObserver()
{

}
//!see observer and related functions to update
void MapObserver::update() {
	//std::cout << "notified\n";
	std::cout << printMap().c_str() << "\n";
	std::cout << printNotifications().c_str();
}

//! Prints out the map and gets open and closed data from all chests
std::string MapObserver::printMap()
{
	//std::cout << MAP_CAST->getCharacterPosition()[0] << "\nxcf" << MAP_CAST->getCharacterPosition()[1];

	std::string returnString = "";
	int counter = 0;
	for (int i = 0; i < MAP_CAST->getRows(); i++) {
		returnString += "\n[";
		for (int j = 0; j < MAP_CAST->getColumns(); j++) {
			if (MAP_CAST->getCharacterPosition()[0] == i && MAP_CAST->getCharacterPosition()[1] == j
				&& MAP_CAST->characterInitialized) {
				returnString += 'C';
			}
			else if (MAP_CAST->getMonstersAtPosition(j, i)->getType() == "monster") {
				std::cout << j << "x y" << i << std::endl;
				returnString += 'm';
			}
			else if (MAP_CAST->getChestAtPosition(j, i)->type == "chest") {
				if (CHEST_OPEN) {
					returnString += '^';
				}
				else {
					returnString += '&';
				}
			}
			else {
				if (MAP_CAST->getMap()[i][j] == "m" || MAP_CAST->getMap()[i][j] == "C")
					MAP_CAST->fillCell(i, j, " ");
				returnString += MAP_CAST->getMap()[i][j];
			}

		}
		returnString += "]";
	}
	returnString += "\n";
	return returnString;
}

//! prints various movement notifications relating the the combination of the map and characters state.
//! perhaps could go in a character observer, it's more specific to a square in the map that the character happens to stand on.
std::string MapObserver::printNotifications() {
	std::string returnString = "";
	int cSquare = MAP_CAST->getCurrentSquare();

	if (!MAP_CAST->getCharacter()->getMoveable()) {
		returnString = "YOU MAKE AN INVALID MOVE\n";
	}
	if (cSquare == -1) {
		returnString = "YOU ARE OVER AN ENTRANCE\n";
	}
	else if (cSquare == 0) {
		returnString = "YOU ARE OVER A TILE\n";
	}
	else if (cSquare == 1) {
		returnString = "YOU ARE OVER AN EXIT\n";
	}
	else if (cSquare < -1 || cSquare > 1 && cSquare != '?') {
		returnString = "YOU ARE STANDING ON SOMETHING YOU SHOULDN'T BE ON\n";
	}
	return returnString;
}