#pragma once
#include <iostream>

class GenericMapItem;
class Character;
class Monster;

class Attack
{
public:
	Attack();
	~Attack();

	//!make an attack. Pass param of attacker for 1. Pass param of defender for 2.
	std::string makeAttack(Character* chara, Monster* mons);
	//!make an attack. Pass param of attacker for 1. Pass param of defender for 2.
	std::string makeAttack(Monster* mons, Character* chara);

	bool calculateHit(Character* chara, Monster* mons, int roll);
	bool calculateHit(Monster* mons, Character* chara, int roll);

	bool crit = false;
	bool miss = false;


};

