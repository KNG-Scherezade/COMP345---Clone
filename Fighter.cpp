//! @file Fighter.cpp
//! @author Patrick Nicoll
//! @brief Implementation of the character type fighter.

#include "Fighter.h"

//! Default constructor
Fighter::Fighter() : Character() {
	//May add unique logic further in project
}

//! Constructor accepting a character starting level
//! @param level	Level character will start at
Fighter::Fighter(int levelVal) : Character(levelVal) {
	//May add unique logic further in project
}

Fighter::~Fighter()
{
}

