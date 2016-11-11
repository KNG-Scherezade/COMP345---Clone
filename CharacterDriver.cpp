#include "stdafx.h"
#include "CharacterDriver.h"
#include "Character.h"
#include "Fighter.h"
#include <fstream>
#include <sstream>


CharacterDriver::CharacterDriver()
{
}


CharacterDriver::~CharacterDriver()
{
}

//! Save a character to a file
//! @param filename	String representing a file name
void CharacterDriver::Save(Character* c, std::string filename)
{
	ofstream outfile;
	outfile.open(filename + ".txt");
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


	outfile.close();
}

//! Load a character from a file
//! @param filename	String representing file name
//! @return A character containing all loaded information
Character* CharacterDriver::Load(std::string filename) {

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
	getline(infile, line);
	std::string type = line.substr(line.find(":") + 2, line.length());

	if (type == "Fighter")
		c = new Fighter();

	//name
	getline(infile, line);
	name = line.substr(line.find(":") + 2, line.length());
	c->setName(name);
	//level
	getline(infile, line);
	level = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setLevel(level);
	//str
	getline(infile, line);
	str = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setStr(str);
	//dex
	getline(infile, line);
	dex = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setDex(dex);
	//con
	getline(infile, line);
	con = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setCon(con);
	//intel
	getline(infile, line);
	intel = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setIntel(intel);
	//wis
	getline(infile, line);
	wis = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setWis(wis);
	//cha
	getline(infile, line);
	cha = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setCha(cha);
	//hp
	getline(infile, line);
	hp = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setHp(hp);
	//max hp
	getline(infile, line);
	maxHp = stoi(line.substr(line.find(":") + 2, line.length()));
	c->setMaxHp(maxHp);

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
	getline(cin, input);
	ss << input;
	if (ss >> decision)
	{
		if (decision == 1)
		{
			Save(character, character->getName());
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
	Character* c;

	// Variable that will hold the option for the text based menu
	int option;

	option = -1;
	input = "";

	// Print options
	cout << "****** Create a Character Menu ******\n";
	cout << "Enter 0 to create a character at Level 1" << endl;
	cout << "Enter 1 to create a character at a specific Level" << endl;
	cout << "Enter 2 to go back to the main menu" << endl;
	getline(cin, input);
	stringstream myStream(input);
	if (myStream >> option) {
		switch (option) {
		case 0:
			c = new Fighter();
			name = inputName();
			c->setName(name);
			return c;
			break;
		case 1:
			// Input for the level
			do {
				cout << "\n\n";
				cout << "Please enter the desired Level of the character" << endl;
				getline(cin, input);

				stringstream myStream(input);
				if (myStream >> level && level >= 1) {
					isInputValid = true;
				}
				else {
					cout << "\n\n";
					cout << "Invalid level, please try again.\n" << endl;
				}
			} while (!isInputValid);
			c = new Fighter(level);
			name = inputName();
			c->setName(name);
			return c;
			break;
		case 2:
			cout << "Go back to main menu" << endl;
			cout << "\n\n";
			return NULL;
			break;
		default:
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
		getline(cin, input);
		name = input;

		if (!name.empty()) {
			cout << "\n";
			cout << "You entered: " << input << "\n";
			cout << "Enter 0 to cancel\n";
			cout << "Enter 1 to confirm\n";

			getline(cin, input);
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
	getline(cin, input);
	Character* c = Load(input + ".txt");
	// Returned item has name error if an error occured, an error message is also shown in the previous method
	if (c == NULL)
	{
		cout << "\nNo character of that name exists\n" << endl;
		return NULL;
	}
	else
	{
		cout << "\n*Character loaded successfully*\n" << endl;
		PrintCharacterBasic(c);
		return c;
	}
	
}

void CharacterDriver::PrintCharacterBasic(Character * c)
{
	cout << c->getType() << endl;
	cout << c->getName() << endl;
	cout << "Level: " << c->getLevel() << endl;
	cout << "Str: " << c->getStr() << "\tDex: " << c->getDex() << "\tCon: " << c->getCon() << "\tInt: " << c->getIntel() << "\tWis: " << c->getWis() << "\tCha: " << c->getCha() << endl;
	cout << "\n";

}
