//!@file Weapon.h
//!  @brief Declaration of weapon equipment
//!
//!  This class represents weapon that is equipped or carried by a character
//!  It makes accessible all stats that weapons have in D20 ruleset
#pragma once
#include "Equipment.h"

//! This class represents weapon that is equipped or carried by a character
class Weapon :
	public Equipment
{
public:
	Weapon();
	Weapon(int w_atk, int w_dmg, int w_level);
	Weapon(int w_level);
	~Weapon();
	int getAttack() { return atk; };
	int getDamage() { return dmg; };
	void setAttack(int w_atk) { atk = w_atk; };
	void setDamage(int w_dmg) { dmg = w_dmg; };
	bool validateEquipment();
	void levelUpEquipment(int w_level);

};

