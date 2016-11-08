//!@file Belt.h
//!  @brief Declaration of belt equipment
//!
//!  This class represents belt that is equipped or carried by a character
//!  It makes accessible all stats that the belt has in D20 ruleset
#pragma once
#include "Equipment.h"
//! This class represents belt that is equipped or carried by a character
class Belt :
	public Equipment
{
public:
	Belt();
	Belt(int b_str, int b_con, int b_level);
	Belt(int b_level);
	~Belt();
	int getConstitution() { return constitution; };
	void setConstitution(int r_con) { constitution = r_con; };
	void setStrength(int r_str) { str = r_str; };
	int getStrength() { return str; };
	bool validateEquipment();
	void levelUpEquipment(int b_level);
};

