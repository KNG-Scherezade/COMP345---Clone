#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Map.h"
#include "Campaign.h"

class CampaignListings
{
public:
	CampaignListings();
	~CampaignListings();

	Campaign* acceptInput4Map();

	void displayMaps();

	int getNumberOfOptions();

	Campaign* campaign;

private:
	void getCapaignNames();
	Campaign* loadCampaignToMemory(std::string path);

	std::vector<std::string> pathNames;

	int index;
};

