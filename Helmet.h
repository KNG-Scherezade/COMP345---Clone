//!@file Helmet.h
//!  @brief Declaration of helmet equipment
//!
//!  This class represents helmet that is equipped or carried by a character
//!  It makes accessible all stats that helmethave in D20 ruleset
#pragma once
#include "Equipment.h"
	//! This class represents a helmet that is equipped or carried by a character
	class Helmet :
		public Equipment
	{
	public:
		Helmet();
		Helmet(int ac, int intel, int wis, int h_level);
		Helmet(int h_level);
		~Helmet();
		int getWisdom() { return wis; };
		int getIntelligence() { return intel; };
		int getArmorClass() { return ac; };
		void setWisdom(int h_wisdom) { wis = h_wisdom; };
		void setIntelligence(int newIntel) { intel = newIntel; };
		void setArmorClass(int h_ac) { ac = h_ac; };
		bool validateEquipment();
		void levelUpEquipment(int h_level);
	private: 
	};
