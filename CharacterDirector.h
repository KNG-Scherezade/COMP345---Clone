//!@file CharacterDirector.h
//!  @brief implementation of the CharacterDirector

//! The director class in the builder pattern
//! Directs the builders to construct a character
#pragma once
#include "CharacterBuilder.h"

//! Director class of the builder pattern that directs the building of a character into of three types: bully, nimble and tank.
class CharacterDirector
{
public:
	CharacterDirector() {};
	~CharacterDirector() {};
	
	// Sets the character to be created
	void setCharacterBuilder(CharacterBuilder* characterBuilder) { c_characterBuilder = characterBuilder; };
	Fighter* getCharacter() {
		return c_characterBuilder->getCharacter();
	}

	// Constructs the character 
	void constructCharacter(int level)
	{
		c_characterBuilder->createNewCharacterProduct();
		c_characterBuilder->buildCharacter(level);
	}

private:
	CharacterBuilder* c_characterBuilder;
};



