//!@file Shield.h
//!  @brief Declaration of shield equipment
//!
//!  This class represents shield that is equipped or carried by a character
//!  It makes accessible all stats that shields have in D20 ruleset
#pragma once
#include "Equipment.h"

//! This class represents a shield that is equipped or carried by a character
class Shield :
	public Equipment
{
public:
	Shield();
	Shield(int s_ac, int s_level);
	Shield(int s_level);
	~Shield();
	int getArmorClass() { return ac; };
	void setArmorClass(int armorClass) { ac = armorClass; };
	bool validateEquipment();
	void levelUpEquipment(int h_level);
	void printItem();
};

