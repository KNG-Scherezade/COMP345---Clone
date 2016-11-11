//!@file Ring.h
//!  @brief Declaration of ring equipment
//!
//!  This class represents ring that is equipped or carried by a character
//!  It makes accessible all stats that rings have in D20 ruleset
#pragma once
#include "Equipment.h"

//! This class represents a ring that is equipped or carried by a character
class Ring :
	public Equipment
{
public:
	Ring();
	Ring(int r_ac, int r_wis, int r_str, int r_cha, int r_con, int r_level);
	Ring(int r_level);
	~Ring();
	int getArmorClass() { return ac; };
	void setArmorClass(int armorClass) { ac = armorClass; };
	bool validateEquipment();
	void levelUpEquipment(int r_level);
	int getWisdom() { return wis; };
	int getStrength() { return str; };
	int getCharisma() { return charisma; };
	int getConstitution() { return constitution; };
	void setWisdom(int r_wisdom) { wis = r_wisdom; };
	void setStrength(int r_str) { str = r_str; };
	void setCharisma(int r_cha) { charisma = r_cha; };
	void setConstitution(int r_con) { constitution = r_con; };
};

