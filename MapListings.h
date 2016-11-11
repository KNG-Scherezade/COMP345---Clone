#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Map.h"

class MapListings
{
public:
	MapListings();
	~MapListings();

	Map* acceptInput4Map();

	void displayMaps();

	int getNumberOfOptions();

private:
	void loadMapsToMemory();
	std::vector<Map*> allMaps;
	std::vector<std::string> pathNames;

	int index;
};

