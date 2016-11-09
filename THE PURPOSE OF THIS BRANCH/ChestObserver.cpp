#include "ChestObserver.h"

#define CHEST_CAST dynamic_cast<Chest*>(getSubject())

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
	std::cout << "This chest corresponds to a level " << CHEST_CAST->getChestState() << " Character !\n\n";
}