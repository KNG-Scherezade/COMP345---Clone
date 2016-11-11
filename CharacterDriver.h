#pragma once
#include "Character.h"
#include "Fighter.h"

class CharacterDriver
{
public:
	CharacterDriver();
	~CharacterDriver();
	Character* Load(std::string filename);
	void Save(Character* c, std::string filename);
	void showSaveDialogue(Character* character);
	Character* createACharacter();
	std::string inputName();
	Character* showLoadMenu();
	void PrintCharacterBasic(Character* c);
};

