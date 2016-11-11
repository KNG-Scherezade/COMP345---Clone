//!@file Shield.cpp
//!  @brief Implementation of Shield equipment
//!
//!  This class represents the shield that is equipped or carried by a character
//!  This class validates the shield and assigns its stats
#include "Shield.h"



//! Default shield constructor sets stats to 1
Shield::Shield()
{
	ac = 1;
	level = 1;
	name = "unknown";
	type = "shield";
}

//! shield constructor sets stats.
//! @param s_ac: the armor class to be set
//! @param s_level the level to be set to
Shield::Shield(int s_ac, int s_level)
{
	ac = s_ac;
	level = s_level;
	name = "unknown";
	type = "shield";
}

//! Shield constructor sets stats based on level.
//! @param s_level the level which designates stat values
Shield::Shield(int s_level)
{
	ac = s_level;
	level = s_level;
	name = "unknown";
	type = "shield";
}


Shield::~Shield()
{
}

//!  Validates the Shield
//! Shield has an armor class attribute that must be between 1 and 5
bool Shield::validateEquipment()
{
	if (ac < 1 || ac > 5)
		return false;
	else if (dex != 0 || str != 0 || wis != 0 || dmg != 0 || atk != 0 || constitution != 0 || charisma != 0)
		return false;
	else
		return true;
}

//! Sets the shield stats to the given level
void Shield::levelUpEquipment(int h_level)
{
	if (h_level > 5)
		ac = 5;
	else
		ac = h_level;
}