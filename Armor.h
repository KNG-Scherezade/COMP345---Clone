//!@file Armor.h
//!  @brief Declaration of armor equipment
//!
//!  This class represents armor that is equipped or carried by a character
//!  It makes accessible all stats that armor has in D20 ruleset
#pragma once
#include "Item.h"
#include "Equipment.h"
//! This class represents armor that is equipped or carried by a character
class Armor : public Equipment
{
public:
	Armor();
	Armor(int armorClass, int a_level);
	Armor(int a_level);
	~Armor();
	int getArmorClass() { return ac; };
	void setArmorClass(int armorClass) { ac = armorClass; };
	bool validateEquipment();
	void levelUpEquipment(int a_level);
};
