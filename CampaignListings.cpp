#include "CampaignListings.h"

#include "MapBuilder.h"
#include "Logger.h"

CampaignListings::CampaignListings()
{
	getCapaignNames();
	campaign = new Campaign();
}


CampaignListings::~CampaignListings()
{
}


#include <Windows.h>
void CampaignListings::getCapaignNames() {

	WIN32_FIND_DATAA campaignFile;
	HANDLE directoryToSearch = FindFirstFileA("./campaigns/*", &campaignFile);

	std::cout << "\n\nSearching Campaign Directory\n";
	if (directoryToSearch)
	{
		do
		{
			std::cout << campaignFile.cFileName << std::endl;
			std::string localPath = campaignFile.cFileName;
			if (localPath != "." && localPath != "..")
				pathNames.push_back("./campaigns/" + localPath);
		} while (FindNextFileA(directoryToSearch, &campaignFile));
	}
	else std::cout << "Directory ./campaigns/* could not be found\n";
	std::cout << "\n";


}

Campaign* CampaignListings::loadCampaignToMemory(std::string path) {

	Campaign* rtnCampaign = new Campaign();
	ifstream ifFile(path);

	string element;

	vector <string> record;
	vector <vector <string>> mapElements;
	while (ifFile)
	{
		if (!getline(ifFile, element)) break;
		if (element == "" || element == " ") continue;
		istringstream stringStream(element);

		while (stringStream)
		{
			if (!getline(stringStream, element, ',')) {
				break;
			}
			if (element == "*****") {
				int rows = mapElements.size();
				int columns = 0;
				if (mapElements.at(0).size() != 0)
					columns = mapElements[0].size();

				Map* newMap = new Map(rows, columns);

				//if (!ifFile.eof())
				//{
				//	cerr << "Load failed. Error occured while building map\n";
				//}

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < columns; j++)
					{
						newMap->fillCell(i, j, mapElements[i][j]);
					}
				}
				rtnCampaign->addMap(newMap);
				mapElements.clear();
				break;
			}
			else
				record.push_back(element);
		}
		if(record.size() > 0)
			mapElements.push_back(record);
		record.clear();
	}
	return rtnCampaign;
}

Campaign* CampaignListings::acceptInput4Map() {
	index = 0;

	bool screwingUp = true;
	while (screwingUp) {
		std::cout << "\nEnter the number of the map you want: \n";
		char input[9001] = "";
		std::cin >> input;
		index = atoi(input) - 1;
		if (index == -1) std::cout << input << " isn't really a map...\n";
		else if(index > pathNames.size() - 1) std::cout << input << " is going to crash the game...\n";
		else {
			std::cout << "Number " << input << " is a pretty good a map...\n";
			screwingUp = false;
		}
	}
	std::cout << "\n";
	Logger log;
	log.LogMap("User selected Campaign " + pathNames.at(index));
	return loadCampaignToMemory(pathNames.at(index));
}

void CampaignListings::displayMaps() {
	int count = 1;
	for each(std::string path in pathNames) {
		std::string mapName;
		mapName = pathNames.at(count - 1);
		mapName.resize(mapName.size() - 4);
		mapName.erase(mapName.begin(), mapName.begin() + 12);

		std::cout << count << ". " << mapName << std::endl;
		count++;
	}
}

int CampaignListings::getNumberOfOptions() {
	return pathNames.size();
}