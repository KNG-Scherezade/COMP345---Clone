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

void MonsterObserver::printMonsterDetails() {
	std::cout << "\nYOU SEE A MONSTER\n";
	bool checkingMonster = true;
	MONSTER_CAST->levelUpStats(CHARACTER->getLevel());
	while (checkingMonster) {
		std::cout << "IT'S STATS ARE:\n" << CHARACTER->lastInteractedMonster->getAttack() << " Atk\n" << CHARACTER->lastInteractedMonster->getHealth() << " HP\n" << CHARACTER->lastInteractedMonster->getLevel() << " Lvl\n";
		std::cout << "Leave monster view ? 1 or 0";
		std::string response;
		std::cin >> response;
		if (response == "1") {
			checkingMonster = false;
		}
	}
}

void MonsterObserver::update() {
	printMonsterDetails();
}