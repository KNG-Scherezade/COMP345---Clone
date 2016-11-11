#pragma once
#include "Map.h"
using namespace std;

//! @file 
//! @brief		Class representing the campaign. Will most likely change in future versions
//!

//! Class representing the campaign.

//! Game rules:	This class allows for the creation of campaigns. Each campaign consists of maps and a name for the campaign.
//!				The name is used to save the campaign as a text file. Currently, the only campaign goal is for the player
//!				to get to the end cell of the last map within the campaign.
//!		
//! Design:		No external libraries have been used. The maps are saved in a vector since there is no telling how many maps
//!				the sure will want to add.

class Campaign
{
public:
	Campaign();
	Campaign(string newName);
	~Campaign();

	//! Initializes the default values for a campaign
	void initializeDefaultCampaign();

	//! Returns a pointer to the vector of maps int the campaign
	vector<Map*>* getMaps();

	//! Adds a new map to the campaign
	//! @param	map	New map to add to the vector of maps
	void addMap(Map *map);

	//! Removes a map from the campaign
	//! @param	map	Map to remove from the vector
	void removeMap(Map *map);

	//! Returns the campaign's name.
	//! @return The campaign's name.
	string getCampaignName();

	//! Returns the number fo maps in the campaign
	//! @return	The number of maps in the campaign.
	int getMapsInCampaign();

	//! Prints the maps within the campaign
	void printMaps();

private:
	// Variables

	//! Vector of maps within the campaign
	vector<Map*>* maps;

	//! Index of the current map the player is in
	int currentMapIndex;

	//! Number of maps in the campaign
	int mapsInCampaign;

	//! Name of the campaign
	string campaignName;
};
