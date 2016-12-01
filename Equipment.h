//!@file Equipment.h
//!  @brief Declaration of equipment
//!
//!  Equipment is used as an interface to distinguish items that are equipment
//!  A common attribute that items have is level and it is made accessible with this class
#pragma once
#include "Item.h"
//!  Equipment is used as an interface to distinguish items that are equipment
class Equipment :
	public Item
{
public:
	virtual bool validateEquipment() { return false; };
	virtual void levelUpEquipment(int e_level) {};
	void setLevel(int e_level) { level = e_level; };
	int getLevel() { return level; };
};