//!@file ItemGenerator.cpp
//! @brief Class which generates random items

#include "ItemGenerator.h"
#include "Helmet.h"
#include "Armor.h"
#include "Belt.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Boots.h"
#include <random>


ItemGenerator::ItemGenerator()
{
}


ItemGenerator::~ItemGenerator()
{
}

//! generate an item based on the given level
//! @param level: the level for the item to be set to.
Item ItemGenerator::generateItem(int level)
{
	mt19937 randomNum;
	randomNum.seed(random_device()());
	// Set random numbers between 0 and 6
	uniform_int_distribution<uint32_t> uint_dist10(0, 6);
	Item item;
	switch (uint_dist10(randomNum))
	{
	case 0:
		item = Helmet(level);
		break;
	case 1:
		item = Armor(level);
		break;
	case 2:
		item = Belt(level);
		break;
	case 3:
		item = Ring(level);
		break;
	case 4:
		item = Shield(level);
		break;
	case 5:
		item = Weapon(level);
		break;
	case 6:
		item = Boots(level);
		break;
	default:
		item = Helmet(level);
	}

	return item;
}
