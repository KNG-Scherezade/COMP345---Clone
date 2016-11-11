#pragma once
//!@file Monster.h
//!  @brief Declaration of DnD monster class
//!
//!  This class is a monster that the character will combat
//!  It contains all basic stats that a monster has in D20

//! declares class variables, accessors and mutators
class Monster
{
public:
	Monster();
	Monster(int m_level);
	~Monster();
	int getHealth() { return hitpoints; }
	int getAttack() { return attack; }
	void setHealth(int newHealth) { hitpoints = newHealth; }
	void setAttack(int newAttack) { attack= newAttack; }
	void setLevel(int newLevel) { level = newLevel; }
	void levelUpStats(int m_level);
	int getLevel() { return level; };
private:
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

