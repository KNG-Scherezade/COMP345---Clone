//!@file Item.cpp
//!  @brief Declaration of an Item
//!
//!  This class represents an item 
//!  Contains stats that d20 items may have, but does not make them accessible. 
#include "Item.h"

Item::Item()
{
	str = 0;
	dex = 0;
	wis = 0;
	constitution = 0;
	charisma = 0;
	ac = 0;
	atk = 0;
	level = 1;
	dmg = 0;
}


Item::~Item()
{
}
std::string Item::toString() {
	return "" + getType() + " of a level " + to_string(level) + " fighter:\nAC: " + to_string(ac) + "\nwis: "
		+ to_string(wis) + "\nstr: " + to_string(str) + "\ncharisma: " + to_string(charisma) + "\nCon: " + to_string(constitution) + "\n";
}