//!@file Boots.h
//!  @brief Declaration of boots equipment
//!
//!  This class represents boots that is equipped or carried by a character
//!  It makes accessible all stats that boots have in D20 ruleset
#pragma once
#include "Equipment.h"
//! This class represents boots that are equipped or carried by a character
class Boots :
	public Equipment
{
public:
	Boots();
	Boots(int b_dex, int b_ac, int b_level);
	Boots(int b_level);
	~Boots();
	int getArmorClass() { return ac; };
	void setArmorClass(int armorClass) { ac = armorClass; };
	int getDexterity() { return dex; };
	void setDexterity(int b_dex) { dex = b_dex; };
	bool validateEquipment();
	void levelUpEquipment(int b_level);
};

