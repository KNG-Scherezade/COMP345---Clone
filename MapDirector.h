//!@file MapDirector.h
//!  @brief implementation of the map director

//! The director class in the builder pattern
//! Directs the builders to construct a map and the treasure and monsters within it
#pragma once
#include <string>
#include "MapBuilder.h"
#include "Map.h"
using namespace std;

//! Directs the builders to construct a map and the treasure and monsters within it
class MapDirector
{
public:
	~MapDirector() { delete m_mapBuilder; };
	void setMapBuilder(MapBuilder* mapBuilder) { m_mapBuilder = mapBuilder; };
	Map* getMap()
	{
		return m_mapBuilder->getMap();
	}
	void constructMap(string fileName) 
	{ 
		m_mapBuilder->createNewMapProduct();
		m_mapBuilder->buildMap(fileName);
		m_mapBuilder->buildMonsters();
		m_mapBuilder->buildTreasure();
	};
private: 
	MapBuilder* m_mapBuilder;
};