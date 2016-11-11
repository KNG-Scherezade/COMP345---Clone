//!@file LevelMapBuilder.h
//!  @brief delcaration of the LevelMapBuilder

//!  This class implements the build functions declared by the MapBuilder
//!  The LevelMapBuilder builds the map based on a save file and a given level 
//!  and creates a list of monsters and treasure contained within the map based on the given level
#pragma once
#include "MapBuilder.h"
//! This class implements the build functions declared by the MapBuilder
class LevelMapBuilder :
	public MapBuilder
{
public:
	LevelMapBuilder();
	LevelMapBuilder(int m_level);
	~LevelMapBuilder();
	virtual void buildMonsters();
	virtual void buildMap(string fileName);
	virtual void buildTreasure();
	void printTreasure(vector<vector<Item>>* treasureList);
	void printMonsters(vector<Monster>* monsters);
private:
	int level;
};