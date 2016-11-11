//!@file Ring.cpp
//!  @brief Implementation of Ring equipment
//!
//!  This class represents the ring that is equipped or carried by a character
//!  This class validates the ring and assigns its stats
#include "Ring.h"

//! Default ring constructor sets stats to 1
Ring::Ring()
{
	ac = 1;
	wis = 1;
	str = 1;
	charisma = 1;
	constitution = 1;
	level = 1;
	name = "unknown";
	type = "ring";
}


//! Ring constructor sets stats.
//! @param r_ac: the armor class to be set
//! @param r_wis the value of wisdom to be set
//! @param r_cha the value of charisma to be set
//! @param r_str the value of strength to be set
//! @param r_con the value of consitution to be set
//! @param r_level the level to be set to
Ring::Ring(int r_ac, int r_wis, int r_str, int r_cha, int r_con, int r_level)
{
	ac = r_ac;
	wis = r_wis;
	str = r_str;
	charisma = r_cha;
	constitution = r_con;
	level = r_level;
	name = "unknown";
	type = "ring";
}

//! Ring constructor sets stats based on level.
//! @param r_level the level which designates stat values
Ring::Ring(int r_level)
{
	levelUpEquipment(r_level);
	level = r_level;
	name = "unknown";
	type = "ring";
}

Ring::~Ring()
{
}

//!  Validates the ring
//! Ring has an armor class attribute that must be between 1 and 5
//! Ring has an wisdom attribute that must be between 1 and 5
//! Ring has an strength attribute that must be between 1 and 5
//! Ring has an charisma attribute that must be between 1 and 5
//! Ring has an constitution attribute that must be between 1 and 5
bool Ring::validateEquipment()
{
	if (ac < 1 || ac > 5 ||
		wis < 1 || wis > 5 ||
		str < 1 || str > 5 ||
		constitution < 1 || constitution> 5 ||
		charisma < 1 || charisma> 5)
		return false;
	else if (dex != 0 || dmg != 0 || atk != 0)
		return false;
	else
		return true;
}


//! Sets the ring stats to the given level
void Ring::levelUpEquipment(int r_level)
{
	if (r_level > 5)
	{
		ac = 5;
		wis = 5;
		str = 5;
		charisma = 5;
		constitution = 5;
	}
	else {
		ac = r_level;
		wis = r_level;
		str = r_level;
		charisma = r_level;
		constitution = r_level;
		level = r_level;
	}
}
