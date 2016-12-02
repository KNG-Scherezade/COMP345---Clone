#include "CharacterDriver.h"
#include "Character.h"
#include "Fighter.h"
#include "ItemCreationDriver.h"
#include <fstream>
#include <sstream>
#include <vector>
#include<iostream>
#include "CharacterDirector.h"
#include "CharacterBullyBuilder.h"
#include "CharacterNimbleBuilder.h"
#include "CharacterTankBuilder.h"

CharacterDriver::CharacterDriver()
{
	log = new Logger();
}


CharacterDriver::~CharacterDriver()
{
	delete log;
}

//! Save a character to a file
//! @param filename	String representing a file name
void CharacterDriver::save(Character* c, std::string filename)
{
	Item* temp;

	ofstream outfile;

	// Save stats
	outfile.open("./Characters/" + filename + ".txt");
	outfile.clear();
	outfile << "type: " << c->getType() << endl;
	outfile << "name: " << c->getName() << endl;
	outfile << "level: " << c->getLevel() << endl;
	outfile << "str: " << c->getStr() << endl;
	outfile << "dex: " << c->getDex() << endl;
	outfile << "con: " << c->getCon() << endl;
	outfile << "int: " << c->getIntel() << endl;
	outfile << "wis: " << c->getWis() << endl;
	outfile << "cha: " << c->getCha() << endl;
	outfile << "hp: " << c->getHp() << endl;
	outfile << "max hp: " << c->getMaxHp() << endl;

	// Save equipment
	temp = c->getHelmet();
	if (temp != NULL)
		outfile << "helmet: " << c->getHelmet()->getName() << endl;
	else
		outfile << "helmet: -" << endl;
	temp = c->getArmor();
	if (temp != NULL)
		outfile << "armor: " << c->getArmor()->getName() << endl;
	else
		outfile << "armor: -" << endl;
	temp = c->getRing();
	if (temp != NULL)
		outfile << "ring: " << c->getRing()->getName() << endl;
	else
		outfile << "ring: -" << endl;
	temp = c->getBelt();
	if (temp != NULL)
		outfile << "belt: " << c->getBelt()->getName() << endl;
	else
		outfile << "belt: -" << endl;
	temp = c->getBoots();
	if (temp != NULL)
		outfile << "boots: " << c->getBoots()->getName() << endl;
	else
		outfile << "boots: -" << endl;
	temp = c->getShield();
	if (temp != NULL)
		outfile << "shield: " << c->getShield()->getName() << endl;
	else
		outfile << "shield: -" << endl;
	temp = c->getWeapon();
	if (temp != NULL)
		outfile << "weapon: " << c->getWeapon()->getName() << endl;
	else
		outfile << "weapon: -" << endl;
	
	// Save inventory
	std::vector<Item*>* inv = c->getInventory();

	outfile << "inventory: " << endl;
	if (inv != NULL) {
		{
			for (int i = 0; inv->size(); i++)
				outfile << "- " << inv->at(i)->getName() << ", " << inv->at(i)->getType() << endl;
		}
	}
	outfile.close();
	log->LogGame("Character saved");
}

//! Load a character from a file
//! @param filename	String representing file name
//! @return A character containing all loaded information
Character* CharacterDriver::load(std::string filename) {

	Character* c = NULL;
	std::string name;
	int level;
	int str;
	int dex;
	int con;
	int intel;
	int wis;
	int cha;
	int hp;
	int maxHp;
	std::string temp;

	ItemCreationDriver icd = ItemCreationDriver();

	std::string line;
	ifstream infile;

	infile.open(filename);
	// return if the file name is wrong
	if (infile.is_open() == false)
	{
		cout << "\nUnable to open file\n";
		// wrong file name, return NULL
		return NULL;
	}

	try {

		std::getline(infile, line);
		std::string type = line.substr(line.find(":") + 2, line.length());

		if (type == "Fighter")
			c = new Fighter();

		//name
		std::getline(infile, line);
		name = line.substr(line.find(":") + 2, line.length());
		c->setName(name);
		//level
		std::getline(infile, line);
		level = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setLevel(level);
		//str
		std::getline(infile, line);
		str = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setStr(str);
		//dex
		std::getline(infile, line);
		dex = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setDex(dex);
		//con
		std::getline(infile, line);
		con = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setCon(con);
		//intel
		std::getline(infile, line);
		intel = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setIntel(intel);
		//wis
		std::getline(infile, line);
		wis = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setWis(wis);
		//cha
		std::getline(infile, line);
		cha = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setCha(cha);
		//hp
		std::getline(infile, line);
		hp = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setHp(hp);
		//max hp
		std::getline(infile, line);
		maxHp = stoi(line.substr(line.find(":") + 2, line.length()));
		c->setMaxHp(maxHp);

		std::getline(infile, line);
		if (!infile.eof()) {
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Helmet helmet = static_cast<Helmet&>(icd.loadItem(temp + ".txt"));
				Helmet* helmPtr = &helmet;
				c->setHelmet(helmPtr);
			}
			//armor
			std::getline(infile, line);
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Armor armor = static_cast<Armor&>(icd.loadItem(temp + ".txt"));
				Armor* armPtr = &armor;
				c->setArmor(armPtr);
			}
			//ring
			std::getline(infile, line);
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Ring ring = static_cast<Ring&>(icd.loadItem(temp + ".txt"));
				Ring* ringPtr = new Ring();
				ringPtr->setName(ring.getName());
				c->setRing(ringPtr);
				//delete ringPtr;
			}
			//belt
			std::getline(infile, line);
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Belt belt = static_cast<Belt&>(icd.loadItem(temp + ".txt"));
				Belt* beltPtr = &belt;
				c->setBelt(beltPtr);
			}
			//boots
			std::getline(infile, line);
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Boots boots = static_cast<Boots&>(icd.loadItem(temp + ".txt"));
				Boots* bootPtr = &boots;
				c->setBoots(bootPtr);
			}
			//shield
			std::getline(infile, line);
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Shield shield = static_cast<Shield&>(icd.loadItem(temp + ".txt"));
				Shield* shPtr = &shield;
				c->setShield(shPtr);
			}
			//weapon
			std::getline(infile, line);
			temp = line.substr(line.find(":") + 2, line.length());
			if (temp != "-") {
				Weapon weapon = static_cast<Weapon&>(icd.loadItem(temp + ".txt"));
				Weapon* weapPtr = &weapon;
				c->setWeapon(weapPtr);
			}
		}
		//inventory
	std:getline(infile, line);
		std::string tempType;
		while (!infile.eof()) {
			std::getline(infile, line);
			temp = line.substr(line.find("-") + 2, line.find(",") - 1);
			tempType = line.substr(line.find(",") + 1, line.length());
			if (tempType == "helmet") {
				Helmet helmet = static_cast<Helmet&>(icd.loadItem(temp + ".txt"));
				Helmet* helPtr = &helmet;
				c->addToInventory(helPtr);
			}
			else if (tempType == "armor") {
				Armor armor = static_cast<Armor&>(icd.loadItem(temp + ".txt"));
				Armor* armPtr = &armor;
				c->addToInventory(armPtr);
			}
			else if (tempType == "belt") {
				Belt belt = static_cast<Belt&>(icd.loadItem(temp + ".txt"));
				Belt* beltPtr = &belt;
				c->addToInventory(beltPtr);
			}
			else if (tempType == "ring") {
				Ring ring = static_cast<Ring&>(icd.loadItem(temp + ".txt"));
				Ring* ringPtr = &ring;
				c->addToInventory(ringPtr);
			}
			else if (tempType == "boots") {
				Boots boots = static_cast<Boots&>(icd.loadItem(temp + ".txt"));
				Boots* bootsPtr = &boots;
				c->addToInventory(bootsPtr);
			}
			else if (tempType == "shield") {
				Shield shield = static_cast<Shield&>(icd.loadItem(temp + ".txt"));
				Shield* shieldPtr = &shield;
				c->addToInventory(shieldPtr);
			}
			else {
				Weapon weapon = static_cast<Weapon&>(icd.loadItem(temp + ".txt"));
				Weapon* weapPtr = &weapon;
				c->addToInventory(weapPtr);
			}

		}

		infile.close();

		//Set modifiers
		c->setStr_mod(c->getModifier(str));
		c->setDex_mod(c->getModifier(dex));
		c->setCon_mod(c->getModifier(con));
		c->setIntel_mod(c->getModifier(intel));
		c->setWis_mod(c->getModifier(wis));
		c->setCha_mod(c->getModifier(cha));
		//ac
		c->calculateAc();
		//attack bonus
		c->calculateBaseAttackBonus();
		//damage bonus
		c->calculateDamageBonus();
	}
	catch (exception e) {
		c = new Character();
	}
	return c;
}

//! Prompt user to save character
//! @param character	Character to be saved
void CharacterDriver::showSaveDialogue(Character* character)
{
	string input;
	stringstream ss;
	int decision;
	cout << "Would you like to save this character?\n[1] yes\n[2] no\n";
	std::getline(cin, input);
	ss << input;
	if (ss >> decision)
	{
		if (decision == 1)
		{
			save(character, character->getName());
		}
		else
			return;
	}
	else
		cout << "Invalid option";
}

//! Allows the user to create a charcter
//! @return Character object
Character* CharacterDriver::createACharacter() {
	string input;
	string name;
	int level;
	bool isInputValid;
	Character* c = NULL;

	// Variable that will hold the option for the text based menu
	int option;

	option = -1;
	input = "";

	// Print options
	cout << "****** Create a Character Menu ******\n";


	//cout << "Enter 0 to create a character at Level 1" << endl;
	//cout << "Enter 1 to create a character at a specific Level" << endl;
	//cout << "Enter 2 to go back to the main menu" << endl;
	//std::getline(cin, input);
	//stringstream myStream(input);
	//if (myStream >> option) {
	//	switch (option) {
	//	case 0:
	//		c = new Fighter();
	//		name = inputName();
	//		c->setName(name);
	//		return c;
	//		break;
	//	case 1:
	//		// Input for the level
	//		do {
	//			cout << "\n\n";
	//			cout << "Please enter the desired Level of the character" << endl;
	//			std::getline(cin, input);

	//			stringstream myStream(input);
	//			if (myStream >> level && level >= 1) {
	//				isInputValid = true;
	//			}
	//			else {
	//				cout << "\n\n";
	//				cout << "Invalid level, please try again.\n" << endl;
	//			}
	//		} while (!isInputValid);
	//		c = new Fighter(level);
	//		name = inputName();
	//		c->setName(name);
	//		return c;
	//		break;
	//	case 2:
	//		cout << "Go back to main menu" << endl;
	//		cout << "\n\n";
	//		return c;
	//		break;
	//	default:
	//		return c;
	//		break;
	//	}
	//}
	//return c;

	cout << "Enter 0 to select the level and class of the character" << endl;
	cout << "Enter 1 to go back to the main menu" << endl;
	std::getline(cin, input);
	stringstream myStream(input);
	if (myStream >> option) {
		switch (option) {
		case 0:
			// Input for the level
			do {
				cout << "\n\n";
				cout << "Please enter the desired Level of the character" << endl;
				std::getline(cin, input);

				stringstream myStream(input);
				if (myStream >> level && level >= 1) {
					isInputValid = true;
				}
				else {
					cout << "\n\n";
					cout << "Invalid level, please try again.\n" << endl;
				}
			} while (!isInputValid);
			name = inputName();
			break;
		case 1:
			cout << "Go back to main menu" << endl;
			cout << "\n\n";
			return c;
			break;
		default:
			return c;
			break;
		}
	}

	// Once level and name have been set, the character's class must be selected
	c = selectFighterClass(level);
	c->setName(name);
	return c;
}

//! Asks the user to select a type of fighter class from
//! bully, nimble and tank.
Character* CharacterDriver::selectFighterClass(int level)
{
	string input;
	// Variable that will hold the option for the text based menu
	int option;
	Character* c = NULL;
	bool isInputValid;
	option = -1;

	// Setting up director
	CharacterDirector characterDirector;
	// Setting up builders
	CharacterBullyBuilder* characterBullyBuilder;
	CharacterNimbleBuilder* characterNimbleBuilder;
	CharacterTankBuilder* characterTankBuilder;
	Fighter* fighter;
	cout << "Enter 0 to create a Bully fighter" << endl;
	cout << "Enter 1 to create a Nimble fighter" << endl;
	cout << "Enter 2 to create a Tank fighter" << endl;

	std::getline(cin, input);
	stringstream myStream(input);
	if (myStream >> option) {
		switch (option) {
		case 0:
			// Create a bully using the builder pattern
			characterBullyBuilder = new CharacterBullyBuilder();
			characterDirector.setCharacterBuilder(characterBullyBuilder);
			characterDirector.constructCharacter(level);
			fighter = characterBullyBuilder->getCharacter();
			return fighter;
			break;
		case 1:
			// Create nimble using the builder pattern
			characterNimbleBuilder = new CharacterNimbleBuilder();
			characterDirector.setCharacterBuilder(characterNimbleBuilder);
			characterDirector.constructCharacter(level);
			fighter = characterNimbleBuilder->getCharacter();
			return fighter;
			break;
		case 2:
			// Create a tank using the builder pattern
			characterTankBuilder = new CharacterTankBuilder();
			characterDirector.setCharacterBuilder(characterTankBuilder);
			characterDirector.constructCharacter(level);
			fighter = characterTankBuilder->getCharacter();
			return fighter;
			break;
		default:
			return c;
			break;
		}
	}
}

//! Accepts input to use as the name of the object being worked on (map, campaign, character)
std::string CharacterDriver::inputName()
{
	bool isInputValid = false;
	string input = "";
	string name = "";
	int option = -1;

	do {
		cout << "\n";
		cout << "Enter the name:\n";
		std::getline(cin, input);
		name = input;

		if (!name.empty()) {
			cout << "\n";
			cout << "You entered: " << input << "\n";
			cout << "Enter 0 to cancel\n";
			cout << "Enter 1 to confirm\n";

			std::getline(cin, input);
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					cout << "\n\n";
					isInputValid = false;
					break;

				case 1:
					cout << "\n\n";
					isInputValid = true;
					break;

				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		}
		else {
			cout << "Cannot enter an empty string. Please try again.\n";
		}
	} while (!isInputValid);
	return name;
}

Character* CharacterDriver::showLoadMenu()
{
	std::string input;
	cout << "\nEnter the filename of the character (without file extension)\n";
	std::getline(cin, input);
	Character* c = load("./characters/" + input + ".txt");

	if (c == NULL)
	{
		cout << "\nNo character of that name exists\n" << endl;
		log->LogGame("Character of that name does not exist");
		return NULL;
	}
	else
	{
		cout << "\n*Character loaded successfully*\n" << endl;
		log->LogGame("Character loaded");
		printCharacterBasic(c);
		return c;
	}

}

void CharacterDriver::printCharacterBasic(Character * c)
{
	cout << c->getType() << endl;
	cout << c->getName() << endl;
	cout << "Level: " << c->getLevel() << endl;
	cout << "Str: " << c->getStr() << "\tDex: " << c->getDex() << "\tCon: " << c->getCon() << "\tInt: " << c->getIntel() << "\tWis: " << c->getWis() << "\tCha: " << c->getCha() << endl;
	cout << "\n";

}

void CharacterDriver::selectItemToEquip(Character* c)
{
	std::string input;
	int option;

	cout << "Select the number of the item you would like to equip." << endl;
	c->printInventory();
	std::getline(cin, input);
	stringstream myStream(input);
	if (myStream >> option) {
		if (option >= 0 && option < c->getInventory()->size()) {
			c->equip(option);
		}
		else
			cout << "Invalid position." << endl;
	}
	else
		cout << "Invalid input." << endl;
}

void CharacterDriver::selectItemToUnequip(Character* c)
{
	std::string input;
	int option;

	cout << "Select the number of the item you would like to unequip." << endl;
	c->printEquipped();
	std::getline(cin, input);
	stringstream myStream(input);
	if (myStream >> option) {
		if (option >= 0 && option < 7) {
			c->unequip(option);
		}
		else
			cout << "Invalid position." << endl;
	}
	else
		cout << "Invalid input." << endl;

}