
#include <iostream>
#include <fstream>
#include <sstream>
//#include <string>
#include "Helmet.h"
#include "Armor.h"
#include "Belt.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Boots.h"
#include "ItemCreationDriver.h"


//! Displays the item menu and accepts input to guide the item creation process
void ItemCreationDriver::showItemMenu()
{
	string input;

	// Variable that will hold the option for the text based menu
	int option;

	// Variables that will hold input
	string name;
	stringstream myStream;
	int wisdom;
	int intel;
	int ac;
	int level;
	int con;
	int str;
	int dex;
	int cha;
	int atk;
	int dmg;
	Armor armor;
	Helmet helmet;
	Belt belt;
	Boots boots;
	Ring ring;
	Shield shield;
	Weapon weapon;
	name = "";
	option = -1;
	input = "";

	cout << "Press 1 to create armor\n";
	cout << "Press 2 to create a helmet\n";
	cout << "Press 3 to create a belt\n";
	cout << "Press 4 to create boots\n";
	cout << "Press 5 to create a ring\n";
	cout << "Press 6 to create a shield\n";
	cout << "Press 7 to create a weapon\n";
	getline(cin, input);
	myStream << input;
	if (myStream >> option) {
		switch (option) {
		case 0:
			break;

			// Create armmor
		case 1:
			name = enterName();
			level = enterNumber("level");
			myStream >> level;
			ac = enterNumber("armor class");
			armor = Armor(ac, level);
			armor.setName(name);
			if (armor.validateEquipment() == true)
			{
				cout << "Armor: " << armor.getName() << " created with level: " << armor.getLevel() << " armor class: " << armor.getArmorClass() << "\n";
				showSaveDialogue(armor);
			}
			else {
				cout << "Armor class invalid, please enter attribute values between 1 and 5" << "\n";
			}

			break;
			// Helmet
		case 2:
			name = enterName();
			level = enterNumber("level");
			intel = enterNumber("intel");
			ac = enterNumber("armor class");
			wisdom = enterNumber("wisdom");
			helmet = Helmet(ac, intel, wisdom, level);
			helmet.setName(name);
			if (helmet.validateEquipment() == true)
			{
				cout << "Helmet: " << helmet.getName() << " created with level: " << helmet.getLevel() << " armor class: " << helmet.getArmorClass()
					<< " intelligence: " << helmet.getIntelligence() << " wisdom: " << helmet.getWisdom() << "\n";
				showSaveDialogue(helmet);
			}
			else {
				cout << "Helmet invalid, please enter attribute values between 1 and 5" << "\n";
			}
			break;
			// Belt
		case 3:
			name = enterName();
			level = enterNumber("level");
			str = enterNumber("strength");
			con = enterNumber("constitution");
			belt = Belt(str, con, level);
			belt.setName(name);
			if (belt.validateEquipment() == true)
			{
				cout << "Belt: " << belt.getName() << " created with level: " << belt.getLevel() << " strength: " << belt.getStrength()
					<< " constitution: " << belt.getConstitution() << "\n";
				showSaveDialogue(belt);
			}
			else {
				cout << "Belt class invalid, please enter attribute values between 1 and 5" << "\n";
			}
			break;
			// Boots
		case 4:
			name = enterName();
			level = enterNumber("level");
			dex = enterNumber("dexterity");
			ac = enterNumber("armor class");
			boots = Boots(dex, ac, level);
			boots.setName(name);
			if (boots.validateEquipment() == true)
			{
				cout << "Boots: " << boots.getName() << " created with level: " << boots.getLevel() << " Dexterity: " << boots.getDexterity()
					<< " Armor Class: " << boots.getArmorClass() << "\n";
				showSaveDialogue(boots);
			}
			else {
				cout << "Boots class invalid, please enter attribute values between 1 and 5" << "\n";
			}
			break;
			// Ring
		case 5:
			name = enterName();
			level = enterNumber("level");
			ac = enterNumber("armor class");
			wisdom = enterNumber("wisdom");
			str = enterNumber("strength");
			cha = enterNumber("charisma");
			con = enterNumber("constitution");
			ring = Ring(ac, wisdom, str, cha, con, level);
			ring.setName(name);
			if (ring.validateEquipment() == true)
			{
				cout << "Ring: " << ring.getName() << " created with level: " << ring.getLevel() << " Armor Class: " << ring.getArmorClass()
					<< " Wisdom: " << ring.getWisdom() << " Strength: " << ring.getStrength() << " Charisma: " << ring.getCharisma() << " Constitution: " << ring.getConstitution() << "\n";
				showSaveDialogue(ring);
			}
			else {
				cout << "Ring class invalid, please enter attribute values between 1 and 5" << "\n";
			}
			break;
			// Shield
		case 6:
			name = enterName();
			level = enterNumber("level");
			ac = enterNumber("armor class");
			shield = Shield(ac, level);
			shield.setName(name);
			if (shield.validateEquipment() == true)
			{
				cout << "Shield: " << shield.getName() << " created with level: " << shield.getLevel() << " Armor Class: " << shield.getArmorClass() << "\n";
				showSaveDialogue(shield);
			}
			else {
				cout << "Shield class invalid, please enter attribute values between 1 and 5" << "\n";
			}
			break;
			// Weapon
		case 7:
			name = enterName();
			level = enterNumber("level");
			atk = enterNumber("attack");
			dmg = enterNumber("damage");
			weapon = Weapon(atk, dmg, level);
			weapon.setName(name);
			if (weapon.validateEquipment() == true)
			{
				cout << "Weapon: " << weapon.getName() << " created with level: " << weapon.getLevel() << " Attack: " << weapon.getAttack() << " damage: " << weapon.getDamage() << "\n";
				showSaveDialogue(weapon);
			}
			else {
				cout << "Weapon class invalid, please enter attribute values between 1 and 5" << "\n";
			}
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

//! Loads the item in the given file
Item ItemCreationDriver::loadItem(string fileName)
{
	int ac;
	int dex;
	int wis;
	int str;
	int intel;
	int cha;
	int con;
	int dmg;
	int atk;
	int level;
	string name;
	string line;
	string nextAttribute;
	ifstream infile;
	stringstream ss;
	infile.open(fileName);
	// return if the file name is wrong
	if (infile.is_open() == false)
	{
		cout << "\nUnable to open file\n";
		// wrong file name, return error item
		Item errorItem = Item();
		errorItem.setName("error");
		return errorItem;
	}
	getline(infile, line);
	string type = line.substr(line.find(":") + 2, line.length());
	if (type == "helmet")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ss << nextAttribute;
		level = stoi(nextAttribute);
		// armor class
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ss << nextAttribute;
		ac = stoi(nextAttribute);
		// intelligence
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ss << nextAttribute;
		intel = stoi(nextAttribute);
		// wisdom
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ss << nextAttribute;
		wis= stoi(nextAttribute);
		Helmet helmet = Helmet(ac, intel, wis, level);
		helmet.setName(name);
		return helmet;
	}
	else if (type == "armor")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		level = stoi(nextAttribute);
		// armor class
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ac = stoi(nextAttribute);
		Armor armor = Armor(ac, level);
		armor.setName(name);
		return armor;
	}
	else if (type == "belt")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		level = stoi(nextAttribute);
		// strength
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		str = stoi(nextAttribute);
		// constitution
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		con = stoi(nextAttribute);
		Belt belt = Belt(str, con, level);
		belt.setName(name);
		return belt;
	}
	else if (type == "boots")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		level = stoi(nextAttribute);
		// dexterity
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		dex = stoi(nextAttribute);
		// armor class
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ac = stoi(nextAttribute);
		Boots boots = Boots(dex, ac, level);
		boots.setName(name);
		return boots;
	}
	else if (type == "ring")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		level = stoi(nextAttribute);
		// armor class
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ac = stoi(nextAttribute);
		// wisdom
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		wis = stoi(nextAttribute);
		// str
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		str = stoi(nextAttribute);
		// charisma
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		cha = stoi(nextAttribute);
		// constitution
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		con = stoi(nextAttribute);
		Ring ring = Ring(ac, wis, str, cha, con, level);
		ring.setName(name);
		return ring;
	}
	else if (type == "shield")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ss << nextAttribute;
		level = stoi(nextAttribute);
		// armor class
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		ac = stoi(nextAttribute);
		Shield shield= Shield(ac, level);
		shield.setName(name);
		return shield;
	}
	else if (type == "weapon")
	{
		// name
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		name = nextAttribute;
		// level
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		level = stoi(nextAttribute);
		// attack
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		atk = stoi(nextAttribute);
		// damage
		getline(infile, line);
		nextAttribute = line.substr(line.find(":") + 2, line.length());
		dmg = stoi(nextAttribute);
		Weapon weapon= Weapon(atk, dmg, level);
		weapon.setName(name);
		return weapon;
	}

	infile.close();

	// Something wrong must have happened to get here
	Item errorItem = Item();
	errorItem.setName("error");
	return errorItem;
}

void ItemCreationDriver::saveItem(Item item, string fileName)
{
	ofstream outfile;
	if (item.getType() == "helmet")
	{
		Helmet helmet = static_cast<Helmet&>(item);
		helmet.setName(helmet.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << helmet.getType() << "\n";
		outfile << "name: " << helmet.getName() << "\n";
		outfile << "level: " << helmet.getLevel() << "\n";
		outfile << "armor class: " << helmet.getArmorClass() << "\n";
		outfile << "intelligence: " << helmet.getIntelligence() << "\n";
		outfile << "wisdom: " << helmet.getWisdom() << "\n";
	}
	else if (item.getType() == "armor")
	{
		Armor armor = static_cast<Armor&>(item);
		armor.setName(armor.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << armor.getType() << "\n";
		outfile << "name: " << armor.getName() << "\n";
		outfile << "level: " << armor.getLevel() << "\n";
		outfile << "armor class: " << armor.getArmorClass() << "\n";
	}
	else if (item.getType() == "belt")
	{
		Belt belt= static_cast<Belt&>(item);
		belt.setName(belt.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << belt.getType() << "\n";
		outfile << "name: " << belt.getName() << "\n";
		outfile << "level: " << belt.getLevel() << "\n";
		outfile << "strength: " << belt.getStrength() << "\n";
		outfile << "consitution: " << belt.getConstitution() << "\n";
	}
	else if (item.getType() == "boots")
	{
		Boots boots= static_cast<Boots&>(item);
		boots.setName(boots.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << boots.getType() << "\n";
		outfile << "name: " << boots.getName() << "\n";
		outfile << "level: " << boots.getLevel() << "\n";
		outfile << "dexterity: " << boots.getDexterity() << "\n";
		outfile << "armor class: " << boots.getArmorClass()<< "\n";
	}
	else if (item.getType() == "ring")
	{
		Ring ring= static_cast<Ring&>(item);
		ring.setName(ring.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << ring.getType() << "\n";
		outfile << "name: " << ring.getName() << "\n";
		outfile << "level: " << ring.getLevel() << "\n";
		outfile << "armor class: " << ring.getArmorClass() << "\n";
		outfile << "wisdom: " << ring.getWisdom()<< "\n";
		outfile << "strength: " << ring.getStrength()<< "\n";
		outfile << "charisma: " << ring.getCharisma()<< "\n";
		outfile << "constitution: " << ring.getConstitution()<< "\n";
	}
	else if (item.getType() == "shield")
	{
		Shield shield= static_cast<Shield&>(item);
		shield.setName(shield.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << shield.getType() << "\n";
		outfile << "name: " << shield.getName() << "\n";
		outfile << "level: " << shield.getLevel() << "\n";
		outfile << "armor class: " << shield.getArmorClass() << "\n";
	}
	else if (item.getType() == "weapon")
	{
		Weapon weapon= static_cast<Weapon&>(item);
		weapon.setName(weapon.getName());
		outfile.open(fileName + ".txt");
		outfile.clear();
		outfile << "type: " << weapon.getType() << "\n";
		outfile << "name: " << weapon.getName() << "\n";
		outfile << "level: " << weapon.getLevel() << "\n";
		outfile << "attack: " << weapon.getAttack() << "\n";
		outfile << "damage: " << weapon.getDamage() << "\n";
	}
	outfile.close();
}

void ItemCreationDriver::showSaveDialogue(Item item)
{
	string input;
	stringstream ss;
	int decision;
	cout << "Would you like to save this item?\n[1] yes\n[2] no\n";
	getline(cin, input);
	ss << input;
	if (ss >> decision)
	{
		if (decision == 1)
		{
			saveItem(item, item.getName());
		}
		else
			return;
	}
	else
		cout << "Invalid option";
}

void ItemCreationDriver::showLoadMenu()
{
	string input;
	cout << "\nEnter the filename of the item you would like to load (without file extension\n)";
	getline(cin, input);
	Item item = loadItem(input + ".txt");
	// Returned item has name error if an error occured, an error message is also shown in the previous method
	if (item.getName() != "error")
	{
		if (item.getType() == "shield")
		{
			Shield shield = static_cast<Shield&>(item);
			cout << "Shield name: " << shield.getName() << "  level: " << shield.getLevel() << " Armor Class: " << shield.getArmorClass() << "\n";
		}
		else if (item.getType() == "helmet")
		{
			Helmet helmet= static_cast<Helmet&>(item);
			cout << "Helmet name: " << helmet.getName() << " level: " << helmet.getLevel() << " armor class: " << helmet.getArmorClass()
				<< " intelligence: " << helmet.getIntelligence() << " wisdom: " << helmet.getWisdom() << "\n";
		}
		else if (item.getType() == "armor")
		{
			Armor armor = static_cast<Armor&>(item);
			cout << "Armor name: " << armor.getName() << " level: " << armor.getLevel() << " armor class: " << armor.getArmorClass() << "\n";
		}
		else if (item.getType() == "boots")
		{
			Boots boots= static_cast<Boots&>(item);
			cout << "Boots name: " << boots.getName() << " level: " << boots.getLevel() << " Dexterity: " << boots.getDexterity()
				<< " Armor Class: " << boots.getArmorClass() << "\n";
		}
		else if (item.getType() == "ring")
		{
			Ring ring= static_cast<Ring&>(item);
			cout << "Ring name: " << ring.getName() << " level: " << ring.getLevel() << " Armor Class: " << ring.getArmorClass()
				<< " Wisdom: " << ring.getWisdom() << " Strength: " << ring.getStrength() << " Charisma: " << ring.getCharisma() << " Constitution: " << ring.getConstitution() << "\n";
		}
		else if (item.getType() == "weapon")
		{
			Weapon weapon = static_cast<Weapon&>(item);
			cout << "Weapon name: " << weapon.getName() << " level: " << weapon.getLevel() << " Attack: " << weapon.getAttack() << " damage: " << weapon.getDamage() << "\n";
		}
		else if (item.getType() == "belt")
		{
			Belt belt= static_cast<Belt&>(item);
			cout << "Belt name: " << belt.getName() << " level: " << belt.getLevel() << " strength: " << belt.getStrength()
				<< " constitution: " << belt.getConstitution() << "\n";
		}

	}
}

string ItemCreationDriver::enterName()
{
	string name;
	cout << "Enter name of item: ";
	getline(cin, name);
	return name;
}

int ItemCreationDriver::enterNumber(std::string attribute)
{
	int level;
	bool validInput = false;
	while (validInput == false)
	{
		stringstream mystream;
		string input;

		cout << "Enter " << attribute << " of item: ";
		getline(cin, input);
		mystream << input;
		if ((mystream >> level))
			validInput = true;
		else
			cout << "Invalid, please enter a number for " << attribute << "\n";
	}
	return level;
}