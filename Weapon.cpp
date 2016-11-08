//!@file Weapon.cpp
//!  @brief Implementation of weapon equipment
//!
//!  This class represents the weapon that is equipped or carried by a character
//!  This class validates the weapon and assigns its stats
#include "Weapon.h"



//! Default weapon constructor sets stats to 1
Weapon::Weapon()
{
	atk = 1;
	dmg = 1;
	level = 1;
	setName("weapon");
}

//! Weapon constructor sets stats.
//! @param w_atk: the attack to be set
//! @param w_dmg the value of damage to be set
//! @param w_level the level to be set to
Weapon::Weapon(int w_atk, int w_dmg, int w_level)
{
	atk = w_atk;
	dmg = w_dmg;
	level = w_level;
	setName("weapon");
}

//! Weapon constructor sets stats based on level.
//! @param w_level the level which designates stat values
Weapon::Weapon(int w_level)
{
	name = "weapon";
	level = w_level;
	levelUpEquipment(w_level);
}


Weapon::~Weapon()
{
}

//!  Validates the weapon
//! Weapon has an attack attribute that must be between 1 and 5
//! Weapon has an damage attribute that must be between 1 and 5
bool Weapon::validateEquipment()
{
	if (atk < 1 || atk > 5 ||
		dmg < 1 || dmg > 5)
		return false;
	else
		return true;
}

//! Sets the weapon stats to the given level
void Weapon::levelUpEquipment(int w_level)
{
	atk = w_level;
	dmg = w_level;
	level = w_level;
}
