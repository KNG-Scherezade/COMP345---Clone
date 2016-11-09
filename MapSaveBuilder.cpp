//!@file MapSaveBuilder.cpp
//!  @brief implementation of the MapSaveBuilder

//!  This class implements the build functions declared by the MapBuilder
//!  The MapSaveBuilder builds the map based on a save file and creates a list of
//!  monsters and treasure contained within the map
#include "MapSaveBuilder.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Helmet.h"
#include "ItemContainer.h"
#include "ItemGenerator.h"
#include <random>
#include "Helmet.h"
#include "Armor.h"
#include "Belt.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Boots.h"

MapSaveBuilder::MapSaveBuilder()
{
}


MapSaveBuilder::~MapSaveBuilder()
{
}

//! Builds the map based on the given file and stores them in the m_map variable
//! @param fileName: the file in which the map is saved
void MapSaveBuilder::buildMap(string fileName)
{
	vector <vector <string> > mapElements;
	ifstream ifFile(fileName);

	while (ifFile)
	{
		string element;
		if (!getline(ifFile, element)) break;

		istringstream stringStream(element);
		vector <string> record;

		while (stringStream)
		{
			string element;
			if (!getline(stringStream, element, ',')) break;
			record.push_back(element);
		}

		mapElements.push_back(record);
	}

	int rows = mapElements.size();
	int columns = mapElements[0].size();

	m_map = new Map(rows, columns);

	if (!ifFile.eof())
	{
		cerr << "error occured while building map\n";
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			m_map->fillCell(i, j, mapElements[i][j]);
		}
	}
}

//! Builds the monsters within the map 
//! and stores them in the m_monsters variable
void MapSaveBuilder::buildMonsters()
{
	Monster leveledMonster = Monster();
	int rows = m_map->getRows();
	int columns = m_map->getColumns();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (m_map->get(i, j) == "m")
				m_monsters->push_back(leveledMonster);
		}
	}
}

//! Builds the treasure within the map 
//! and stores them in the m_treasure variable
//! The amount of items and the items themselves are
//! generated randomly.
void MapSaveBuilder::buildTreasure()
{
	int rows = m_map->getRows();
	int columns = m_map->getColumns();
	ItemGenerator itemGen = ItemGenerator();
	int treasureCounter = 0;
	mt19937 randomNum;
	// Set random numbers between 0,2 
	uniform_int_distribution<uint32_t> uint_dist10(0, 2);
	for (int i = 0; i < rows; i++)
	{
		// set new count for random amount of items
		randomNum.seed(random_device()());
		for (int j = 0; j < columns; j++)
		{
			if (m_map->get(i, j) == "t")
			{
				// Initialize another vector of items inside m_treasure because it will be filled with items
				m_treasure->push_back(vector<Item>());
				// Generates 1-3 random items inside the chest
				for (int i = 0; i <= uint_dist10(randomNum); i++)
				{
					Item item = itemGen.generateItem(1);
					m_treasure->at(treasureCounter).push_back(item);
				}
				treasureCounter++;
			}
		}
	}
}

//! prints a selected few unique values based on the given treasure list
//! @param treasureList the treasure list to be printed
void MapSaveBuilder::printTreasure(vector<vector<Item>>* treasureList)
{
	int treasureCounter = 1;
	for each (vector<Item> treasure in *treasureList)
	{
		cout << "\nTreasure chest " << treasureCounter++;
		for each (Item item in treasure)
		{
			cout << "\nItem name: " << item.getName();
			cout << " level: " << static_cast<Equipment&>(item).getLevel();
			if (item.getName() == "helmet")
			{
				Helmet helmet = static_cast<Helmet&>(item);
				int dex = helmet.getDexterity();
				cout << " dex: " << dex << " armor class: " << helmet.getArmorClass() << " wisdom: " << helmet.getWisdom();
			}
			else if (item.getName() == "boots")
			{
				Boots boots = static_cast<Boots&>(item);
				int ac = boots.getArmorClass();
				cout << " ac: " << ac << " dexterity: " << boots.getDexterity();
			}
			else if (item.getName() == "armor")
			{
				Armor armor = static_cast<Armor&>(item);
				int ac = armor.getArmorClass();
				cout << " ac: " << ac;
			}
			else if (item.getName() == "ring")
			{
				Ring ring = static_cast<Ring&>(item);
				int cha = ring.getCharisma();
				cout << " charisma: " << cha << " armor class: " << ring.getArmorClass() << " constitution: " << ring.getConstitution() << " strength: " << ring.getStrength() << " wisdom: " << ring.getWisdom();
			}
			else if (item.getName() == "shield")
			{
				Shield shield = static_cast<Shield&>(item);
				int ac = shield.getArmorClass();
				cout << " ac: " << ac;
			}
			else if (item.getName() == "weapon")
			{
				Weapon weapon = static_cast<Weapon&>(item);
				int dmg = weapon.getDamage();
				cout << " damage: " << dmg << " attack: " << weapon.getAttack();
			}
			else if (item.getName() == "belt")
			{
				Belt belt = static_cast<Belt&>(item);
				int str = belt.getStrength();
				cout << " str: " << str << " constitution: " << belt.getConstitution();
			}
		}
	}
}

//! prints a selected few monster stats based on the given monster list
//! @param monsterList the monster list to be printed
void MapSaveBuilder::printMonsters(vector<Monster>* monsters)
{
	int monsterCounter = 1;
	for each (Monster monster in *monsters)
	{
		cout << "\nMonster: " << monsterCounter;
		cout << " level: " << monster.getLevel();
		cout << " attack: " << monster.getAttack();
		cout << " health: " << monster.getHealth();
		monsterCounter++;
	}
}



