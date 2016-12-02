//!@file CharacterBuilder.h
//!  @brief delcaration of the CharacterBuilder

//!  This class declares the build functions implemented by the concrete builders
//!  The character builder is designed to allow easy instantiation of different styles of characters.
#pragma once
#include "Fighter.h"
using namespace std;

//! The character builder interface that the concrete builders implement
class CharacterBuilder
{
public:
	CharacterBuilder() {};
	~CharacterBuilder() {};

	//! Gets the character
	Fighter* getCharacter() { return c_character; };

	//! creates the character
	void createNewCharacterProduct() {c_character = new Fighter();};

	//! Concrete implementation of building a character
	virtual void buildCharacter(int level) = 0;
protected:
	Fighter* c_character;
	Logger log;

};

