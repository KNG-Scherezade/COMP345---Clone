#pragma once

#include "Map.h"
#include "Observable.h"

//!@file Monster.h
//!  @brief Declaration of DnD monster class
//!
//!  This class is a monster that the character will combat
//!  It contains all basic stats that a monster has in D20

//! declares class variables, accessors and mutators
class Monster : public Subject
{
public:
	Monster();
	Monster(int m_level);
	Monster(Map* map, int x, int y);
	Monster(Map* map, int x, int y, int m_level);
	~Monster();
	int getHealth() { return hitpoints; }
	int getAttack() { return attack; }
	void setHealth(int newHealth) { hitpoints = newHealth; }
	void setAttack(int newAttack) { attack= newAttack; }
	void setLevel(int newLevel) { level = newLevel; }
	void levelUpStats(int m_level);

	int getLevel() { return level; };
	int * getPosition() { return position; };

	void setX(int x) { position[0] = x; }
	void setY(int y) { position[0] = y; }

	void notify();
	void attach(Observer* obs);

	Map* getMap() { return mapPtr; }

private:
	int position[2];
	Map* mapPtr;

	int hitpoints;
	int attack;
	int level;
	int str;
	int dex;
	int con;
	int wis; 
	int cha;
	int intel;
};

