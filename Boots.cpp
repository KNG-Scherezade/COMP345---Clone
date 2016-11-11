//!@file Boots.cpp
//!  @brief Implementation of Boots equipment
//!
//!  This class represents the boots that is equipped or carried by a character
//!  This class validates the boots and assigns its stats
#include "Boots.h"

//! Default boots constructor sets stats to 1
Boots::Boots()
{
	dex = 1;
	ac = 1;
	level = 1;
	name = "unknown";
	type = "boots";
}

//! Ring constructor sets stats.
//! @param b_ac: the armor class to be set
//! @param b_dex the value of dexterity to be set
//! @param b_level the level to be set to
Boots::Boots(int b_dex, int b_ac, int b_level)
{
	dex = b_dex;
	ac = b_ac;
	level = b_level;
	name = "unknown";
	type = "boots";
}

//! Boots constructor sets stats based on level.
//! @param b_level the level which designates stat values
Boots::Boots(int b_level)
{
	name = "unknown";
	type = "boots";

	levelUpEquipment(b_level);
}


Boots::~Boots()
{
}

//!  Validates the Boots
//! Boots has a wisdom attribute that must be between 1 and 5
//! Boots has an armor class attribute that must be between 1 and 5
bool Boots::validateEquipment()
{
	if (ac < 1 || ac > 5 ||
		dex < 1 || dex > 5)
		return false;
	else if (str != 0 || wis != 0 || dmg != 0 || atk != 0 || constitution != 0 || charisma != 0)
		return false;
	else
		return true;
}

//! Sets the boots stats to the given level
void Boots::levelUpEquipment(int b_level)
{
	if (b_level > 5)
	{
		dex = 5;
		ac = 5;
	}
	else {
		dex = b_level;
		ac = b_level;
	}
}