#include "GameDriver.h"
#include "character.h"
#include "Monster.h"
#include "MonsterObserver.h"

#include "Map.h"
#include "MapObserver.h"
#include "Campaign.h"

#include "Logger.h"

#include "HumanPlayerStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"

#include "ItemGenerator.h"


GameDriver::GameDriver(Character* chara, Campaign* campaign)
{
	log = new Logger();
	character = chara;
	this->campaign = campaign;
	currentMap = 0;

	setup(chara, currentMap);
	campaign->getMap(currentMap)->notify();

	log->LogGame("Game loop ended, setup ended");
	gameLoop();
}


GameDriver::~GameDriver()
{
}

void GameDriver::setup(Character* chara,  int mapIndex) {
	gameRunning = true;
	map = campaign->getMap(mapIndex);
	log->LogMap("System loads map " + std::to_string(mapIndex) + " of the campaign of " + std::to_string(campaign->getMaps()->size()));
	mo = new MapObserver(map);
	chara->postInitialize(map);
	chara->configurePosition();
	chara->setStrategy(new HumanPlayerStrategy());

	for each(ItemContainer* ic in map->getChests()) {
		ChestObserver* co = new ChestObserver(ic);
		ic->setItemLevels(chara->getLevel());
	}
	log->LogGame("Chests given observers");
	log->LogGame("All chests set to player level");
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
	log->LogGame("monsters set to player level");
	log->LogGame("monsters Given strategies based on mod 2");
}

void GameDriver::gameLoop() {
	while (gameRunning) {
		log->LogGame("Turn sequences start");
		runTurns();
		if (exit) {
			log->LogGame("Game switches maps");
			swapMaps(currentMap);
			for each(ItemContainer* ic in character->getMap()->getChests()) {
				ic->setItemLevels(character->getLevel());
			}
			log->LogGame("Item levels were set");
			map->notify();
			exit = false;
		}
		log->LogGame("Turn sequences end");
	}

	std::cout << "GAME OVER\n";
	if(win)	std::cout << "YOU WIN\n";
	else std::cout << "YOU DIED\nenter a key";
	log->LogGame("Game has been concluded. User returned to main menu");
	getchar();
}
void GameDriver::runTurns() {
	if (character->getHp() <= 0) {
		log->LogCharacter("Character has 0 HP and has died. Game restarting to menu");
		win = false;
		gameRunning = false;
		exit = false;
		cin.ignore();
		return;
	}
	for (int i = 0; i < character->getNumAtks(); i++) {
		log->LogCharacter("Character can move :" + to_string(i) + "/" + to_string(character->getNumAtks()) + "Times");
		int state = character->executeStrategy();
		if (state == 1) { //1 implies interaction over exit point
			currentMap++;
			exit = true;
			return;
		}
		if (state > 0)
			i--;

		for each(Monster* mon in map->getMonsters()) {
			if (mon->dead) {
				ItemContainer* newIC = new ItemContainer(map, mon->getPosition()[0], mon->getPosition()[1]);

				ChestObserver* newCO = new ChestObserver(newIC);
				map->addChest(newIC);
				map->removeMonster(mon);
				log->LogGame("Monster died, was removed and replaced by a chest");
			}
		}
		log->LogGame("Game checks if monsters are dead");
	}
	log->LogGame("Game switches to monster turns");
	for each(Monster* mon in map->getMonsters()) {
			mon->executeStrategy();

	}
	map->notify();
}

void GameDriver::swapMaps(int mapNumber) {
	map->detatch();
	if (mapNumber > campaign->getMaps()->size() - 1) {
		log->LogGame("User is out of maps and has won");
		gameRunning = false;
		win = true;
		return;
	}
	setup(character, mapNumber);
}




