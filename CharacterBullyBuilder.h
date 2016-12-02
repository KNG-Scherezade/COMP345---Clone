//!	 @file CharacterBullyBuilder.h
//!  @brief declaration of concrete builder of the bully fighter
//!
//!  This class builds a bully fighter which has stats tailored for dealing damage
//!  Hitpoints, attack bonus and number of attacks are also set based on the level of the fighter.
//!  The d20 rules followed are: (1) his hit points go up by(1d10 + constitution modifier), 
//!  (2) his attack bonus goes up by one, (3) His number of attacks go up by 1 every 5 levels
//!	 A bully's score is attributed according to Strength, Constitution, Dexterity, Intelligence, Charisma, Wisdom
//!  in that order.
#pragma once
#include "CharacterBuilder.h"

//! concrete character  builder of the bully fighter
class CharacterBullyBuilder :
	public CharacterBuilder
{
public:
	CharacterBullyBuilder();
	~CharacterBullyBuilder();
	// Concrete implementation of building a character
	virtual void buildCharacter(int level);
};

