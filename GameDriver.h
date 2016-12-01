#pragma once

class Character;
class Map;

class GameDriver
{
public:
	GameDriver(Character* chara, Map* map);
	~GameDriver();

	void setup(Character* chara, Map* map);
	void gameLoop();
	void runTurns();

	void swapMaps();

	Character* character;
	Map* map;

	bool gameRunning;
	bool exit;
};

