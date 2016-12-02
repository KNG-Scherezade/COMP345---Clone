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
	std::cout << "\nDetails: \n";
	bool checkingMonster = true;
	while (checkingMonster) {
		std::cout << CHARACTER->lastInteractedMonster->toString() << "\n";
		if (MONSTER_CAST->dead)  std::cout << "\nYOU KILLED IT\n";
		checkingMonster = false;	
	}
}

bool MonsterObserver::checkStatus() {
	return MONSTER_CAST->getCurrentHP() <= 0;
}

