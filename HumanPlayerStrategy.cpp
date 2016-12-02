#include "HumanPlayerStrategy.h"
#include "GenericMapItem.h"
#include "Character.h"
#include "Monster.h"
#include "Attack.h"
#include "Logger.h"

HumanPlayerStrategy::HumanPlayerStrategy()
{
}


HumanPlayerStrategy::~HumanPlayerStrategy()
{
}
#include <sstream>
int HumanPlayerStrategy::decideAction(GenericMapItem* chara){
	int rtn = -1;
	std::string direction;
	std::cout << "Enter \"1\" to do a movement, \"2\" to do an attack, or \"3\" to do a free action\n";
	std::cin >> direction;
	Logger log;
	if (direction == "1"){
		log.LogCharacter("Player is moving");
		move(chara);
	}
	else if (direction == "2"){
		log.LogCharacter("Player is attacking");
		attack(chara);
	}
	else if (direction == "3"){
		log.LogCharacter("Player is interacting. Will have no impact on number of moves");
		rtn = interact(chara);
	}

	
	return rtn;
}

void HumanPlayerStrategy::attack(GenericMapItem*  chara){
	Logger log;
	std::string direction;
	std::cout << "Enter A Direction To Attack of \"l, r, u or d\". U and D allow diagonals:\n";
	std::cin >> direction;
	int msg = ((Character*)chara)->checkLook(direction);
	log.LogCharacter("Player sets attack Direction and checks if monster is located there");
	//MONSTER INTERACTION
	if (msg == -3) {
		std::cout << "\n YOU ATTACK";
		((Character*)chara)->lastInteractedMonster->setAttacked(true);
		Attack atk;
		std::cout << atk.makeAttack(((Character*)chara), ((Character*)chara)->lastInteractedMonster);
		((Character*)chara)->lastInteractedMonster->notify();

	}
	else{
		std::cout << "\n INVALID SQUARE";
		log.LogCharacter("No attack happened. Invalid Square");
	}
}

int HumanPlayerStrategy::interact(GenericMapItem*  chara){
	Logger log;
	std::string direction;
	std::cout << "Enter \"i\" to look at your inventory, enter \"s\" to see your stats, enter \"e\" to interact";
	std::cin >> direction;

	//INTERACT WITH INVENTORY
	if (direction == "i" || direction == "I") {
		bool lookingAtThings = true;
		while (lookingAtThings) {
			std::cout << "\t\nYOUR INVENTORY IS AS FOLLOWS: \n" << std::endl;
			((Character*)chara)->printInventory();
			std::cout << "\t\nYOUR EQUIPS ARE AS FOLLOWS: \n" << std::endl;
			((Character*)chara)->printEquipped();

			std::cout << "Enter \"1\" to equip and item, enter \"2\" to unequip an item, enter \"ANY KEY\" to exit";
			std::cin >> direction;

			cin.ignore();
			if (direction == "1") {
				cout << "Select the number of the item you would like to equip." << endl;
				std::getline(cin, direction);
				stringstream myStream(direction);
				int index;
				if (myStream >> index) {
					if (index >= 0 && index < ((Character*)chara)->getInventory()->size()) {
					((Character*)chara)->equip(index);
					}
					else
						cout << "Invalid position." << endl;
				}
				else
					cout << "Invalid input." << endl;
			}
			else if (direction == "2") {
				cout << "Select the number of the item you would like to unequip." << endl;
				std::getline(cin, direction);
				stringstream myStream(direction);
				int index;
				if (myStream >> index) {
					if (index >= 0 && index < 7) {
						((Character*)chara)->unequip(index);
					}
					else
						cout << "Invalid position." << endl;
				}
				else
					cout << "Invalid input." << endl;
			}
			lookingAtThings = false;
		}
	}
	else if (direction == "s" || direction == "S") {
			std::cout << "\n\nYOUR STATS ARE:\n";
			((Character*)chara)->printStats();
		}
	//INTERACT WITH EXIT POINT
	else if (direction == "e" || direction == "E") {
		if (((Character*)chara)->getMap()->getCurrentSquare() == 1) {
			((Character*)chara)->levelUp();
			CharacterDriver cd;
			cd.save(((Character*)chara), ((Character*)chara)->getName());
			log.LogGame("Character was saved and campaign is now triggered to change");
			std::cout << "\n\nYou Move to an new Room AND GAIN A LEVEL\n";
			return 1;
		}

		// CHECKS FOR LOOK DIRECTIONS
		// CHARACTER CREATES SIMPLE COUT LINES. THIS FILE DOES COMPLEX ONES
		std::cout << "Enter A Direction To Interact of \"l, r, u or d\". U and D allow diagonals:\n";
		std::cin >> direction;
		int msg = ((Character*)chara)->checkLook(direction);
		log.LogGame("A chest was oppened");
		//CHEST INTERACTION
		if (msg == 2) {
			//((Character*)chara)->lastOpenedChest->setItemLevels(((Character*)chara)->getLevel());
			((Character*)chara)->lastOpenedChest->notify();

			log.LogGame("A chest was oppened");
		}
		//MONSTER INTERACTION
		else if (msg == -3) {
			((Character*)chara)->lastInteractedMonster->notify();
			log.LogGame("A monster was examined");
		}
	}
	return 2;
}
void HumanPlayerStrategy::move(GenericMapItem*  chara){
	std::string direction;
	std::cout << "Enter A Direction To Move of \"l, r, u or d\"";
	std::cin >> direction;
	Logger log;

	//MOVEMENT CHECKS

	((Character*)chara)->checkMove(direction);
	log.LogMap("Checked if move was possible");
}