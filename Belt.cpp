// !@file Belt.cpp
//!  @brief Implementation of belt equipment
//!
//!  This class represents the belt that is equipped or carried by a character
//!  This class validates the belt and assigns its stats
#include "Belt.h"

//! Default belt constructor sets stats to 1
Belt::Belt()
{
	str = 1;
	constitution = 1;
	level = 1;
	name = "unknown";
	type = "belt";
}

//! Beltconstructor sets stats.
//! @param b_str: the strength  to be set
//! @param b_con: the constitution to be set
//! @param b_level the level to be set to
Belt::Belt(int b_str, int b_con, int b_level)
{
	str = b_str;
	constitution = b_con;
	level = b_level;
	name = "unknown";
	type = "belt";
}


//! Beltconstructor sets stats based on level.
//! @param b_level the level which designates stat values
Belt::Belt(int b_level)
{
	level = b_level;
	str = b_level;
	constitution = b_level;
	name = "unknown";
	type = "belt";
}


Belt::~Belt()
{
}

//!  Validates the armor
//! Belt has a strength attribute that must be between 1 and 5
//! Belt has a constitution attribute that must be between 1 and 5
bool Belt::validateEquipment()
{
	if (str < 1 || str > 5 ||
		constitution < 1 || constitution> 5)
		return false;
	else if (ac != 0 || wis != 0 || dex != 0 || dmg != 0 || atk != 0 || charisma != 0)
		return false;
	else
		return true;
}

//! Sets the belt stats to the given level
void Belt::levelUpEquipment(int b_level)
{
	if (b_level > 5)
	{
		str = 5;
		constitution = 5;
	}
	else {
		str = b_level;
		constitution = b_level;
	}
}