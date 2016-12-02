#pragma once

class Character;
class Campaign;
class Map;
class MapObserver;
class Logger;

class GameDriver
{
public:
	GameDriver(Character* chara, Campaign* campaign);
	~GameDriver();

	void setup(Character* chara, int mapIndex);
	void gameLoop();
	void runTurns();

	void swapMaps(int map);

	Character* character;
	Campaign* campaign;
	Map* map;
	MapObserver* mo;

	int currentMap;

	bool gameRunning;
	bool exit;
	bool win = false;

	Logger* log;
};

