#pragma once
#include <iostream>
#include <vector>
#include "character.h"
#include "CharacterDriver.h"
class CharacterListings
{
public:
	CharacterListings();
	~CharacterListings();


	Character* acceptInput4Character();

	void displayCharacters();

	int getNumberOfOptions();

private:
	void getCharacterPathNames();

	std::vector<std::string> pathNames;

};

