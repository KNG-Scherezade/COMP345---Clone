//!@file MapSaveBuilder.h
//!  @brief delcaration of the MapSaveBuilder

//!  This class implements the build functions declared by the MapBuilder
//!  The MapSaveBuilder builds the map based on a save file and creates a list of
//!  monsters and treasure contained withinn the map
#pragma once
#include "MapBuilder.h"
#include <string>
using namespace std;
//! This class implements the build functions declared by the MapBuilder
class MapSaveBuilder :
	public MapBuilder
{
public:
	MapSaveBuilder();
	~MapSaveBuilder();
	virtual void buildMonsters();
	virtual void buildMap(string fileName);
	virtual void buildTreasure();
	void printTreasure(vector<vector<Item>>* treasureList);
	void printMonsters(vector<Monster>* monsters);
};



