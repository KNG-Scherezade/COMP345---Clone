#include "MonsterObserver.h"
#include "Monster.h"
#include <iostream>

#define MONSTER_CAST dynamic_cast<Monster*>(getSubject())
#define CHARACTER MONSTER_CAST->getMap()->getCharacter()

MonsterObserver::MonsterObserver(Subject* sub) : Observer(sub)
{
}


MonsterObserver::~MonsterObserver()
{
}
void MonsterObserver::update() {
	MONSTER_CAST->dead = checkStatus();
	printMonsterDetails();

}

void MonsterObserver::printMonsterDetails() {
	std::cout << "\nYOU INTERACT WITH A MONSTER\n";
	bool checkingMonster = true;
	while (checkingMonster) {
		std::cout << "IT'S STATS ARE:\n" << CHARACTER->lastInteractedMonster->getAttack() << " Atk\n" << CHARACTER->lastInteractedMonster->getHealth() << " HP\n" << CHARACTER->lastInteractedMonster->getLevel() << " Lvl\n";
		if (MONSTER_CAST->dead)  std::cout << "\nYOU KILLED IT\n";
		std::cout << "Leave monster view ? 1 or 0";
		std::string response;
		std::cin >> response;
		if (response == "1") {
			checkingMonster = false;
		}
	}
}

bool MonsterObserver::checkStatus() {
	return MONSTER_CAST->getHealth() <= 0;
}

