#include "Campaign.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Campaign::Campaign()
{
	initializeDefaultCampaign();
}

Campaign::Campaign(string newName) : campaignName(newName)
{
	initializeDefaultCampaign();
}

Campaign::~Campaign()
{
	// Clear memory
	for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
		delete (maps->at(i));
		maps->at(i) = 0;
	}

	delete maps;
	maps = 0;
}

void Campaign::initializeDefaultCampaign()
{
	currentMapIndex = 0;
	mapsInCampaign = 0;
	maps = new vector<Map*>();

	// Code that may be used in a later version if we decide to have a standard default map for a campaign.
	//maps->push_back(new Map()); 
	//maps->at(currentMapIndex)->fillCell(0, 0, 's');
	//maps->at(currentMapIndex)->fillCell(1, 1, 'e');

	/*for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
		maps->at(i)->printMap();
	}*/
}

vector<Map*>* Campaign::getMaps()
{
	return maps;
}

void Campaign::addMap(Map * map)
{

	mapsInCampaign++;
	currentMapIndex++;
	maps->push_back(new Map (*map));
	cout << "Map " << map->getMapName() << " has been added to campaign " << campaignName << endl;
}

void Campaign::removeMap(Map * map)
{
	mapsInCampaign--;
	currentMapIndex--;
	// Remove the map from the campaign

	auto it = std::find(maps->begin(), maps->end(), map);
	if (it != maps->end()) {
		maps->erase(it);
	}

	delete map;
	map = 0;
}

string Campaign::getCampaignName()
{
	return campaignName;
}

int Campaign::getMapsInCampaign()
{
	return mapsInCampaign;
}

void Campaign::printMaps()
{
	if (maps->size() == 0) {
		cout << campaignName << " does not contain any maps\n";
	}
	else {
		cout << "Maps in campaign: " << campaignName << ":\n";
		for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
			maps->at(i)->printMap();
		}
	}
}