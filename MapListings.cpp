#include "MapListings.h"

#include "MapBuilder.h"

MapListings::MapListings()
{
	loadMapsToMemory();
}


MapListings::~MapListings()
{
	int count = 0;
	for each(Map* map in allMaps) {
		if(count != index)
			delete map;
		count++;
	}
}

Map* MapListings::acceptInput4Map() {
	index = 0;

	bool screwingUp = true;
	while (screwingUp) {
		std::cout << "\nEnter the number of the map you want: \n";
		char input[9001] = "";
		std::cin >> input;
		index = atoi(input) - 1;
		if (index == -1) std::cout << input << " isn't really a map...\n";
		else if(index > allMaps.size() - 1) std::cout << input << " is going to crash the game...\n";
		else {
			std::cout << "Number " << input << " is a pretty good a map...\n";
			screwingUp = false;
		}
	}
	std::cout << "\n";
	return allMaps.at(index);
}

void MapListings::displayMaps() {
	int count = 1;
	for each(Map* map in allMaps) {
		std::string mapName;
		if (map->getMapName() == "") {
			mapName = pathNames.at(count - 1);
			mapName.resize(mapName.size() - 4);
			mapName.erase(mapName.begin(), mapName.begin() + 7);
		}
		else
			std::string mapName = map->getMapName();

		std::cout << count << ". " << mapName << std::endl;
		count++;
	}
}

#include <Windows.h>
void MapListings::loadMapsToMemory() {

	WIN32_FIND_DATAA mapFile;
	HANDLE directoryToSearch = FindFirstFileA("./maps/*", &mapFile);

	std::cout << "\n\nSearching Map Directory\n";
	if (directoryToSearch)
	{
		do
		{
			std::cout << mapFile.cFileName << std::endl;
			std::string localPath = mapFile.cFileName;
			if(localPath != "." && localPath != "..")
				pathNames.push_back("./maps/" + localPath);
		} while (FindNextFileA(directoryToSearch, &mapFile));
	}
	else std::cout << "Directory ./maps/* could not be found\n";
	std::cout << "\n";

	for each(std::string fileName in pathNames) {
		vector <vector <string>> mapElements;
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
				if (!getline(stringStream, element, ','))
					break;
				record.push_back(element);
			}

			mapElements.push_back(record);
		}

		int rows = mapElements.size();
		int columns = 0;
		if (mapElements.size() != 0)
			columns = mapElements[0].size();

		Map* newMap = new Map(rows, columns);

		if (!ifFile.eof())
		{
			cerr << "Load failed. Error occured while building map\n";
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				newMap->fillCell(i, j, mapElements[i][j]);
			}
		}
		allMaps.push_back(newMap);
	}
}

int MapListings::getNumberOfOptions() {
	return allMaps.size();
}