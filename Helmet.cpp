//!@file Helmet.cpp
//!  @brief Implementation of Helmet equipment
//!
//!  This class represents the helmet that is equipped or carried by a character
//!  This class validates the helmet and assigns its stats
#include "Helmet.h"


//! Default helmet constructor sets stats to 1
Helmet::Helmet()
{
	setName("helmet");
	wis = 1;
	dex = 1;;
	ac = 1;
	level = 1;
}

//! Helmet constructor sets stats.
//! @param h_ac: the armor class to be set
//! @param h_wis the value of wisdom to be set
//! @param h_dex the value of dexterity to be set
//! @param h_level the level to be set to
Helmet::Helmet(int h_ac, int h_dex, int h_wis, int h_level)
{
	wis = h_wis;
	dex = h_dex;
	ac = h_ac;
	level = h_level;
	setName("helmet");
}

//! Helmet constructor sets stats based on level.
//! @param h_level the level which designates stat values
Helmet::Helmet(int h_level)
{
	name = "helmet";
	wis = h_level;
	dex = h_level;
	ac = h_level;
	level = h_level;

}


Helmet::~Helmet()
{
}

//!  Validates the helmet
//! helmet has an armor class attribute that must be between 1 and 5
//! helmet has an wisdom attribute that must be between 1 and 5
//! helmet has an dexterity attribute that must be between 1 and 5
bool Helmet::validateEquipment()
{
	if (ac < 1 || ac > 5 || dex < 1 || dex > 5 || wis < 1 || wis > 5)
		return false;
	else
		return true;
}

//! Sets the helmet stats to the given level
void Helmet::levelUpEquipment(int h_level)
{
	wis = h_level;
	dex = h_level;
	ac = h_level;
}
