#pragma once
#include<iostream>
class Logger;
class Character;

//class CharacterDriver		Cause lol circular dependencies
//{ 
//public:
//	CharacterDriver();
//	~CharacterDriver();
//	Character* load(std::string filename);
//	void save(Character* c, std::string filename);
//	void showSaveDialogue(Character* character);
//	Character* createACharacter();
//	std::string inputName();
//	Character* showLoadMenu();
//	void printCharacterBasic(Character* c);
//	void selectItemToEquip(Character* c);
//	void selectItemToUnequip(Character* c);
//};


class CharacterDriver
{
public:
	CharacterDriver();
	~CharacterDriver();
	Character* load(std::string filename);
	void save(Character* c, std::string filename);
	void showSaveDialogue(Character* character);
	Character* createACharacter();
	std::string inputName();
	Character* showLoadMenu();
	void printCharacterBasic(Character* c);
	void selectItemToEquip(Character* c);
	void selectItemToUnequip(Character* c);
private:
	Logger* log;
};