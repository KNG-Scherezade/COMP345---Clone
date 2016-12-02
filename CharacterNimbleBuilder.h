//!	 @file CharacterNimbleBuilder.h
//!  @brief declaration of concrete builder of the nimble fighter
//!
//!  This class builds a nimble fighter which has stats tailored for evasion
//!  Hitpoints, attack bonus and number of attacks are also set based on the level of the fighter.
//!  The d20 rules followed are: (1) his hit points go up by(1d10 + constitution modifier), 
//!  (2) his attack bonus goes up by one, (3) His number of attacks go up by 1 every 5 levels
//!	 A nimble fighter's score is attributed according to Dexterity, Constitution, Strength, Intelligence, Charisma, Wisdom
//!  in that order.
#pragma once
#include "CharacterBuilder.h"

//! concrete character  builder of the nimble fighter
class CharacterNimbleBuilder :
	public CharacterBuilder
{
public:
	CharacterNimbleBuilder();
	~CharacterNimbleBuilder();

	// Concrete implementation of building a character
	virtual void buildCharacter(int level);
};

