#include "HumanPlayerStrategy.h"
#include "GenericMapItem.h"
#include "Character.h"
#include "Monster.h"

HumanPlayerStrategy::HumanPlayerStrategy()
{
}


HumanPlayerStrategy::~HumanPlayerStrategy()
{
}
#include <sstream>
int HumanPlayerStrategy::decideAction(GenericMapItem* chara){
	int rtn = 0;
	std::string direction;
	std::cout << "Enter \"1\" to do a movement, \"2\" to do an attack, or \"3\" to do a free action\n";
	std::cin >> direction;
	if (direction == "1"){
		move(chara);
	}
	else if (direction == "2"){
		attack(chara);
	}
	else if (direction == "3"){
		rtn = interact(chara);
	}

	
	return rtn;
}

void HumanPlayerStrategy::attack(GenericMapItem*  chara){
	std::string direction;
	std::cout << "Enter A Direction To Attack of \"l, r, u or d\". U and D allow diagonals:\n";
	std::cin >> direction;

	int msg = ((Character*)chara)->checkLook(direction);
	//MONSTER INTERACTION
	if (msg == -3) {
		std::cout << "\n YOU ATTACK";
		((Character*)chara)->lastInteractedMonster->setAttacked(true);

		((Character*)chara)->lastInteractedMonster->setHealth(0);
		((Character*)chara)->lastInteractedMonster->notify();

	}
	else{
		std::cout << "\n INVALID SQUARE";
	}
}

int HumanPlayerStrategy::interact(GenericMapItem*  chara){
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
			std::cout << "\n\tEnter any key to continue\n" << std::endl;
			char stopVar;//since getchar was failing
			std::cin >> stopVar;
			lookingAtThings = false;
		}
	}
	else if (direction == "s" || direction == "S") {
		((Character*)chara)->printEquipped();
			std::cout << "\n\nYOUR STATS ARE:\n";
			((Character*)chara)->printStats();
		}
	//INTERACT WITH EXIT POINT
	else if (direction == "e" || direction == "E") {
		if (((Character*)chara)->getMap()->getCurrentSquare() == 1) {
			((Character*)chara)->setLevel(((Character*)chara)->getLevel() + 1);
			CharacterDriver cd;
			cd.save(((Character*)chara), ((Character*)chara)->getName());

			std::cout << "\n\nYou Move to an new Room AND GAIN A LEVEL\n";
			return 1;
		}

		// CHECKS FOR LOOK DIRECTIONS
		// CHARACTER CREATES SIMPLE COUT LINES. THIS FILE DOES COMPLEX ONES
		std::cout << "Enter A Direction To Interact of \"l, r, u or d\". U and D allow diagonals:\n";
		std::cin >> direction;
		int msg = ((Character*)chara)->checkLook(direction);
		//CHEST INTERACTION
		if (msg == 2) {
			((Character*)chara)->lastOpenedChest->notify();
		}
		//MONSTER INTERACTION
		else if (msg == -3) {
			((Character*)chara)->lastInteractedMonster->notify();
		}
	}
}
void HumanPlayerStrategy::move(GenericMapItem*  chara){
	std::string direction;
	std::cout << "Enter A Direction To Move of \"l, r, u or d\"";
	std::cin >> direction;

	//MOVEMENT CHECKS
	((Character*)chara)->checkMonsters(direction);
	((Character*)chara)->checkMove(direction);

}