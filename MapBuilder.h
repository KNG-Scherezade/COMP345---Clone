//!@file MapBuilder.h
//!  @brief declaration of the map builder

//!  This class declares the build functions implemented by the concrete builders
//!  Map Builders are designed to build a map and give a list of monsters and treasure on the map
#pragma once
#include <string>
#include "Map.h"
#include "Monster.h"
#include <vector>
#include "Item.h"
#include "ItemContainer.h"
using namespace std;
//! This class declares the build functions implemented by the concrete builders
class MapBuilder
{
public:
	~MapBuilder() { delete m_map; delete m_monsters; delete m_treasure; };
	Map* getMap() { return m_map; };
	vector<Monster>* getMonsters() { return m_monsters; };
	vector<vector<Item>>* getTreasure() { return m_treasure; };
	void setMap(string fileName);
	void createNewMapProduct() { m_map = new Map(); m_monsters = new vector<Monster>(); m_treasure = new vector<vector<Item>>(); };
	virtual void buildMap(string fileName) = 0;
	virtual void buildMonsters() = 0;
	virtual void buildTreasure() = 0;
private:

protected:
	Map* m_map;
	vector<Monster>* m_monsters;
	vector<vector<Item>>* m_treasure;

};