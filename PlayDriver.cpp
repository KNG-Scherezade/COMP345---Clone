//#include "MapListings.h"
//#include "CharacterListings.h"
//#include "MapObserver.h"
//#include "Boots.h"
//#include "Ring.h"
//
//#include "ItemGenerator.h"
//#include "MonsterObserver.h"
//#include <iostream>
//
//
//int playDriver() {
//	// *********************************************************INITIALIZATION AND SELECTION OF MAP AND CHARACTER *********************************************************
//
//	Map* map = nullptr;
//	Character* chara = nullptr;
//
//	std::cout << "------------------------------\n";
//
//	MapListings* mapChoiceOptions = new MapListings();
//	CharacterListings* characterChoiceOptions = new CharacterListings();
//
//	std::cout << "------------------------------\n";
//
//	if (mapChoiceOptions->getNumberOfOptions() == 0 && characterChoiceOptions->getNumberOfOptions() == 0) {
//		std::cout << "No maps or characters\nGo make some.\n";
//		getchar();
//		return -1;
//	}
//	else if (mapChoiceOptions->getNumberOfOptions() == 0 || characterChoiceOptions->getNumberOfOptions() == 0) {
//		std::cout << "No maps xor characters\nGo make some.\n";
//		getchar();
//		return -2;
//	}
//
//	bool repeat = true;
//	while (repeat) {
//
//		mapChoiceOptions->displayMaps();
//		map = mapChoiceOptions->acceptInput4Map();
//		MapObserver* mo1 = new MapObserver(map);
//		std::cout << mo1->printMap() << "\n";
//
//		characterChoiceOptions->displayCharacters();
//		chara = characterChoiceOptions->acceptInput4Character();
//		std::cout << chara->toString();
//		//Map pointer has not been set yet
//
//		std::cout << "\nYou're fine with this, right ?\nGive a 1 if yes and a 0 if no\n";
//		char confirmation[9001] = "";
//		std::cin >> confirmation;
//
//		if (strcmp("0", confirmation) == 0) {
//			std::cout << "\nWe'll do it again then...\n";
//			delete mo1;
//		}
//		else if (strcmp("1", confirmation) == 0) {
//			std::cout << "\nLets move on...\n";
//			//Set the map pointer
//			chara->postInitialize(map);
//			repeat = false;
//		}
//		else
//			std::cout << "What is a " << confirmation << " ?\n";
//	}
//	delete mapChoiceOptions;
//	delete characterChoiceOptions;
//	// ******************************************************************************************************************
//
//
//
//
//
//
//
//
//	// ********************************************************* START OF GAME LOOP AND GAME PLAY *********************************************************
//
//	map->notify();
//	for each(ItemContainer* ic in map->getChests()) {
//		ChestObserver* co = new ChestObserver(ic);
//	}
//	for each(Monster* mon in map->getMonsters()) {
//		MonsterObserver* mo = new MonsterObserver(mon);
//	}
//	bool gameRunning = true;
//	while (gameRunning) {
//
//
//
//		char direction;
//		std::cout << "Enter A Direction To Move of \"l, r, u or d\". Enter \"i\" for inventory or enter \"e\" to interact:\n";
//		std::cin >> direction;
//
//
//		//INTERACT WITH INVENTORY
//		if (direction == 'i' || direction == 'I') {
//			bool lookingAtThings = true;
//			while (lookingAtThings) {
//				std::cout << "\t\nYOUR INVENTORY IS AS FOLLOWS: \n" << std::endl;
//				chara->printInventory();
//				std::cout << "\t\nYOUR EQUIPS ARE AS FOLLOWS: \n" << std::endl;
//				chara->printEquipped();
//				std::cout << "\n\tEnter any key to continue\n" << std::endl;
//				char stopVar;//since getchar was failing
//				std::cin >> stopVar;
//				lookingAtThings = false;
//			}
//
//		}
//
//		//INTERACT WITH EXIT POINT
//		else if (direction == 'e' || direction == 'E') {
//			if (map->getCurrentSquare() == 1) {
//				chara->setLevel(chara->getLevel() + 1);
//				CharacterDriver cd;
//				cd.save(chara, chara->getName());
//				
//				std::cout << "\n\nYou Move to an new Room AND GAIN A LEVEL\n";
//				gameRunning = false;
//				break;
//			}
//
//			// CHECKS FOR LOOK DIRECTIONS
//			// CHARACTER CREATES SIMPLE COUT LINES. THIS FILE DOES COMPLEX ONES
//			std::cout << "Enter A Direction To Interact of \"l, r, u or d\". U and D allow diagonals:\n";
//			std::cin >> direction;
//			int msg = chara->checkLook(direction);
//
//
//
//			//CHEST INTERACTION
//			if (msg == 2) {
//				chara->lastOpenedChest->notify();
//			}
//
//			//MONSTER INTERACTION
//			else if (msg == -3) {
//				chara->lastInteractedMonster->notify();			
//			}
//			map->notify();
//		}
//		//MOVEMENT CHECKS
//		else {
//			chara->checkMove(direction);
//		}
//	}
//
//
//	std::cout << "GAME OVER\n";
//	getchar();	getchar();
//
//	// ********************************************************* *********************************************************
//
//}
//
//
//int main() {
//	playDriver();
//	return 0;
//}
