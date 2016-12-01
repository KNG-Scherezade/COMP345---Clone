#include "GameDriver.h"
#include "character.h"
#include "Monster.h"
#include "MonsterObserver.h"

#include "Map.h"

#include "HumanPlayerStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"

#include "ItemGenerator.h"


GameDriver::GameDriver(Character* chara, Map* map)
{
	setup(chara, map);

	map->notify();

	gameLoop();
}


GameDriver::~GameDriver()
{
}

void GameDriver::setup(Character* chara, Map* map) {
	gameRunning = true;
	character = chara;
	this->map = map;

	chara->configurePosition();
	chara->setStrategy(new HumanPlayerStrategy());

	for each(ItemContainer* ic in map->getChests()) {
		ChestObserver* co = new ChestObserver(ic);
	}

	int count = 0;
	for each(Monster* mon in map->getMonsters()) {
		mon->levelUpStats(chara->getLevel());
		MonsterObserver* mo = new MonsterObserver(mon);
		if (count % 2 == 0) {
			mon->setStrategy(new AggressorStrategy());
		}
		else {
			mon->setStrategy(new FriendlyStrategy());
		}
	}
}

void GameDriver::gameLoop() {
	while (gameRunning) {
		runTurns();
		if (exit)
			swapMaps();
	}

	std::cout << "GAME OVER\n";
	getchar();	getchar();

}
void GameDriver::runTurns() {
		int state = character->executeStrategy();
		if (state == 1) {
			gameRunning = false;
		}
		for each(Monster* mon in map->getMonsters()) {
			if (mon->dead) {
				ItemContainer* newIC = new ItemContainer(map, mon->getPosition()[0], mon->getPosition()[1]);
				ItemGenerator ig;
				newIC->addItem(ig.generateItemPtr(character->getLevel()));

				ChestObserver* newCO = new ChestObserver(newIC);
				map->addChest(newIC);
				map->removeMonster(mon);
			}
			else {
				mon->executeStrategy();
			}
		}
		map->notify();
}

void GameDriver::swapMaps() {}




