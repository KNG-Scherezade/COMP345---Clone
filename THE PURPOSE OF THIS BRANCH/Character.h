//! The character is an object that can move on the map. It has stats and can interact with the environment.

//! The design takes a pointer to the map and allows the object to take user interaction.
//! User interaction alters the state of the map.

//!Vanilla C++

#pragma once
#include "Observable.h"
#include "Map.h"

class Map;

class Character
{
public:
	Character(Map *map);
	~Character();

	void configurePosition();
	void checkMove(char moveDir);
	int checkLook(char lookDir);
	int StandingOn(int col, int row);
	std::string checkInteraction(int row, int col, int type);

	int getLevel();
	bool getMoveable();

	void setMoveable(bool movable);
	void setLevel(int lvl);

private:
	Map* mapPtr;
	int level;
	bool moveable;
};

