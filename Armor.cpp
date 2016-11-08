//!@file Armor.cpp
//!  @brief Implementation of armor equipment
//!
//!  This class represents armor that is equipped or carried by a character
//!  This class validates armor and assigns its stats
#include "Armor.h"

//! Default armor constructor sets stats to 1
Armor::Armor()
{
	ac = 1;
	level = 1;
	setName("armor");
}

//! Armor constructor sets stats.
//! @param armorClass: the armor class to be set
//! @param a_level the level to be set to
Armor::Armor(int armorClass, int a_level)
{
	ac = armorClass;
	name = "armor";
	level = a_level;
}

//! Armor constructor sets stats based on level.
//! @param a_level the level which designates stat values
Armor::Armor(int a_level)
{
	level = a_level;
	ac = a_level;
	name = "armor";
}


Armor::~Armor()
{
}


//!  Validates the armor
//! Armor has an armor class attribute that must be between 1 and 5
bool Armor::validateEquipment()
{
	if (ac < 1 || ac > 5 )
		return false;
	else
		return true;
}

//! Sets the armor stats to the given level
void Armor::levelUpEquipment(int a_level)
{
	ac = a_level;
}
