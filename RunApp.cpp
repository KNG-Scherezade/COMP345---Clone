//! @file 
//! @brief Driver file to create and execute the test suite and to launch the Map and Campaign Editor
//!
//! Brief instruction on how to set CppUnit:
//! from: http ://www.comp.nus.edu.sg/~cs3215/tools/cppunitAll.html
//!
//!	First, to install cppUnit :
//!
//!	 1. Unpack the CppUnit archive (https://sourceforge.net/projects/cppunit/files/cppunit/1.12.1/) to a directory of your choice, in this example I assume it is D:\. 
//!  2. Go to D:/cppunit-1.12.1/src and open the CppUnitLibraries.dsw in Visual Studio.
//!  3. Select the cppunit project in the Solution Explorer and go to 'Project > Properties > Configuration Properties > Librarian > General. Put "Debug\cppunit.lib" in the ‘Output FileEtextbox. 
//!  4. Right-click on the cppunit project in the Solution Explorer pane and choose Build.
//!  5. After successful compilation, D:/cppunit-1.12.1/lib/cppunit.lib is produced which you then need to setup the Visual Studio Linker with (see below).

//!
//! To setup a project from scratch for Compilation / Linking:
//!
//!	  1. Activate 'Project > Properties > C/C++ >  Code Generation > Runtime Library > Multi - threaded Debug DLL'
//!	  2. Go to 'Project > Properties > C/C++ > General'. Put "D:\cppunit-1.12.1\include" in the 'Additional Include Directories' text box.
//!	  3. Go to 'Project > Properties > Linker > Input'. Put "D:\cppunit-1.12.1\lib\cppunit.lib" in the 'Additional Dependences' text box.
//!	  4. Go to 'Project > Properties > Build Events > Post-Build Event'. Put '"$(TargetPath)"' in the 'Command Line' textbox.Put 'Unit Tests...' in the 'Description' textbox.



#include <iostream>
#include <sstream>
#include <string>
#include<fstream>

#include "Map.h"
#include "Campaign.h"
#include "MapDirector.h"
#include "MapBuilder.h"
#include "MapSaveBuilder.h"
#include "ItemCreationDriver.h"
#include "CharacterDriver.h"

#include "MonsterObserver.h"

#include "CampaignListings.h"

#include "CharacterListings.h"
#include "MapObserver.h"
#include "Boots.h"
#include "Ring.h"

#include "ItemGenerator.h"

#include <iostream>

#include "AbstractStrategy.h"
#include "HumanPlayerStrategy.h"
#include "FriendlyStrategy.h"
#include "AggressorStrategy.h"

#include "Character.h"
#include "Fighter.h"

#include "GameDriver.h"


using namespace std;
//adding comment just so i could push
//! Runs the driver to launch the map and campaign editor.
void runDriver();

//! Shows the main menu for the map and campaign editor.
void showMainMenuForMapAndCampaign();

//! Start the main game demo.
int playDriver();

//! Allows the user to select which map to edit.
//! @param	maps	Vector of all current existing maps.
vector<Map*>* selectMapToEdit(vector<Map*>* maps);

//! Allows the user to select which campaign to edit
//!
//! @param	campaigns	Vector of all current existing campaigns	
//! @param	maps		Vector of all current existing maps.
void selectCampaignToEdit(vector<Campaign*>* campaigns, vector<Map*>* maps);
//Map* editMap(Map* map, int mapNumber, string mapName);

//! Allows the user to edit a map.
//!
//! @param	maps		Vector of all current existing maps	
//! @param	mapNumber	The map's position in the vector.
//! @param	mapName		The map's name.
void editMap(Map* map, int mapNumber, string mapName);

//! Allows the user to select how to edit a campaign.
//!
//!	@param	campaigns	Vector of all existing campaigns
//! @param	maps		Vector of all current existing maps	
void editCampaign(Campaign* campaign, vector<Map*>* maps);

//! Allows the user to add maps to a campaign.
//!
//!	@param	campaigns	Vector of all existing campaigns
//! @param	maps		Vector of all current existing maps
void addMapToCampaign(Campaign* campaign, vector<Map*>* maps);

//! Allows the user to remove maps from a campaign.
//!
//!	@param	campaigns	Vector of all existing campaigns
//! @param	maps		Vector of all current existing maps
void removeMapFromCampaign(Campaign* campaign);

//! Allows the user to save a new map
//!
//! @param	maps		Vector of all current existing maps
void saveMaps(vector<Map*>* maps);

//! Allows the user to save a new campaign.
//!
//!	@param	campaigns	Vector of all existing campaigns
void saveCampaigns(vector<Campaign*>* campaigns);

void loadMaps(vector<Map*>* maps);

// Methods that accept in out from thr user

//! Accepts user to input the number of columns a new map will have.
//! @return	The number of columns for a new map.
int inputColumnsForNewMap();

//! Accepts user to input the number of rows a new map will have.
//! @return	The number of rows for a new map.
int inputRowsForNewMap();

//! Accepts user to input the row index to edit for a map
//! @param	rowsInMap	The number of rows in the map.
//!
//! @return	The row index to edit.
int inputRowIndexToEdit(int rowsInMap);

//! Accepts user to input the column index to edit for a map
//! @param	rcolumnsInMap	The number of columns in the map.
//!
//! @return	The row index to edit.
int inputColumnIndexToEdit(int columnsInMap);

//! Accepts user to input a char to insert into a map.
//! @param	row			The row index where the char will be inputed.
//! @param	columns		The column index where the char will be inputed.	
//!
//! @return	The char inputed
string inputCharObject(int row, int column);

//! Allows the user to input the name for a map or a campaign.
//! @return	The name for a map or campaign.
string inputName();


//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
int main(int argc, char* argv[])
{
	/*
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( suite );
	// Change the default outputter to a compiler error format outputter
	runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
	std::cerr ) );
	// Run the tests.
	bool wasSucessful = runner.run();
	getchar();
	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
	*/
	runDriver();
	//return 0;
}

//! Shows a TUI (Text User Interface) to the user to allow them to select different options.
void showMainMenuForMapAndCampaign() {

	//Character variables
	Character* character = NULL;

	//Item variables
	Item item;

	//Map & Campaign variables
	vector<Map*>* maps = new vector<Map*>();
	vector<Campaign*>* campaigns = new vector<Campaign*>();

	//Drivers
	ItemCreationDriver icd = ItemCreationDriver();
	CharacterDriver cd = CharacterDriver();

	bool exitMenu;
	string input;

	// Variable that will hold the option for the text based menu
	int option;

	// Variables that will hold input
	int rows;
	int columns;
	string name;

	// Menu loop
	do {
		// Initialize values
		name = "";
		rows = -1;
		columns = -1;
		option = -1;
		input = "";
		exitMenu = false;

		// Print options
		cout << "****** Map and Campaign Editor Main Menu ******\n";
		cout << "Please select an option.\n\n";
		cout << "Enter 0 to exit.\n";
		cout << "Enter 1 to create a map.\n";
		cout << "Enter 2 to edit a map.\n";
		cout << "Enter 3 to create a campaign.\n";
		cout << "Enter 4 to edit a campaign.\n";
		cout << "Enter 5 to save the created maps.\n";
		cout << "Enter 6 to save the created campaigns.\n";
		cout << "Enter 7 to load existing maps from files.\n";
		cout << "Enter 8 to create an item.\n";
		cout << "Enter 9 to load an item.\n";
		cout << "Enter 10 to create a character.\n";
		cout << "Enter 11 to save the character.\n";
		cout << "Enter 12 to load an existing character.\n";
		cout << "Enter 13 to view character's inventory.\n";
		cout << "Enter 14 to view character's equipment.\n";
		cout << "Enter 15 to add items to inventory.\n";
		cout << "Enter 16 to equip an item.\n";
		cout << "Enter 17 to unequip an item.\n";
		cout << "Enter 20 to play the game.\n";
		cout << "Enter 21 to edit an item.\n";
		getline(cin, input);
		stringstream myStream(input);
		if (myStream >> option) {
			switch (option) {
			case 0:
				exitMenu = true;
				break;

			case 1:
				cout << "\n\n";
				rows = inputRowsForNewMap();
				columns = inputColumnsForNewMap();
				name = inputName();
				maps->push_back(new Map(rows, columns, name));
				cout << "Created the following map: " << name << "\n";
				maps->back()->printMap();
				break;

			case 2:
				cout << "\n\n";
				maps = selectMapToEdit(maps);
				break;

			case 3:
				cout << "\n\n";
				name = inputName();
				campaigns->push_back(new Campaign(name));
				break;

			case 4:
				cout << "\n\n";
				selectCampaignToEdit(campaigns, maps);
				break;

			case 5:
				cout << "\n\n";
				saveMaps(maps);
				break;

			case 6:
				cout << "\n\n";
				saveCampaigns(campaigns);
				break;

			case 7:
				cout << "\n\n";
				loadMaps(maps);
				break;

			case 8:
				cout << "\n\n";
				icd.showItemMenu();
				break;

			case 9:
				cout << "\n\n";
				item = icd.showLoadMenu();
				break;

			case 10:
				cout << "\n\n";
				character = cd.createACharacter();
				if (character != NULL)
					cd.showSaveDialogue(character);
				break;

			case 11:
				cout << "\n\n";
				if (character != NULL)
					cd.save(character, character->getName());
				else
					cout << "There is no character to save." << endl;
				break;

			case 12:
				cout << "\n\n";
				character = cd.showLoadMenu();
				break;

			case 13:
				cout << "\n\n";
				if (character != NULL)
					character->printInventory();
				else
					cout << "No character selected" << endl;
				break;

			case 14:
				cout << "\n\n";
				if (character != NULL)
					character->printEquipped();
				else
					cout << "No character selected" << endl;
				break;

			case 15:
				cout << "\n\n";
				if (character != NULL) {
					if (item.getName() != "unknown")
					{
						character->addToInventory(&item);
					}
					else
						cout << "No item is selected" << endl;
				}
				else
					cout << "No character selected" << endl;
				break;

			case 16:
				cout << "\n\n";
				if (character != NULL)
					cd.selectItemToEquip(character);
				else
					cout << "No character selected." << endl;
				break;

			case 17:
				cout << "\n\n";
				if (character != NULL)
					cd.selectItemToUnequip(character);
				else
					cout << "No character selected." << endl;
				break;

			case 20:
				cout << "\n\n";
				playDriver();
				break;

			case 21:
				cout << "\n\n";
				if (item.getName() != "unknown")
					icd.showEditDialogue(item);
				else
					cout << "There is no item selected." << endl;
				break;

			default:
				cout << "\n\n";
				cout << "Invalid option, please try again.\n" << endl;
				break;
			}
		}
		else {
			cout << "\n\n";
			cout << "Invalid option, please try again.\n" << endl;
		}

	} while (!exitMenu);

	// Delete all maps in vector
	for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
		delete(maps->at(i));
		maps->at(i) = 0;
	}
	delete maps;

	// Delete all campaigns
	for (std::vector<Campaign*>::size_type i = 0; i != campaigns->size(); i++) {
		delete(campaigns->at(i));
		campaigns->at(i) = 0;
	}
	delete campaigns;
}

vector<Map*>* selectMapToEdit(vector<Map*>* maps)
{
	int mapCounter = -1;
	for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
		mapCounter++;
		cout << "Map  number " << i << " :  \n" << endl;
		maps->at(i)->printMap();
		cout << "\n";
	}

	// Exit option if there are no maps to edit.
	if (mapCounter == -1) {
		cout << "There are no existing maps to edit. Returning to the main menu\n";
		return maps;
	}

	string input = "";
	int option = 0;
	bool valid = false;
	do {
		cout << "*** Select map to edit ***\n";
		cout << "Enter the number associated with the map to edit: \n";
		getline(cin, input);
		stringstream myStream(input);
		if (myStream >> option) {
			if (option <= mapCounter) {
				valid = true;

				// Get map
				//Map* map = maps->at(option);
				// Edit map
				//map = editMap(map, option);
				editMap(maps->at(option), option, maps->at(option)->getMapName());

				// No need to delete map since the new keyword was not used.
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		}
		else {
			cout << "Invalid option, please try again.\n" << endl;
		}
	} while (!valid);
	return maps; ////////////////////////////////////////////////////////////////////// redundant?
}

void selectCampaignToEdit(vector<Campaign*>* campaigns, vector<Map*>* maps)
{
	int campaignCounter = -1;
	for (std::vector<Campaign*>::size_type i = 0; i != campaigns->size(); i++) {
		campaignCounter++;
		cout << "Campaign  number " << i << " : " << campaigns->at(i)->getCampaignName() << "\n" << endl;
		cout << "\n";
	}

	// Exit option if there are no maps to edit.
	if (campaignCounter == -1) {
		cout << "There are no existing campaigns to edit. Returning to the previous menu\n";
		return;
	}

	string input = "";
	int option = 0;
	bool valid = false;
	do {
		cout << "*** Select campaign to edit ***\n";
		cout << "Enter the number associated with the campaign to edit: \n";
		getline(cin, input);
		stringstream myStream(input);
		if (myStream >> option) {
			if (option <= campaignCounter) {
				valid = true;

				editCampaign(campaigns->at(option), maps);

				// No need to delete map since the new keyword was not used.
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		}
		else {
			cout << "Invalid option, please try again.\n" << endl;
		}
	} while (!valid);
}

void editMap(Map * map, int mapNumber, string mapName)
{
	int inputValue = 0;
	bool isInputValid = false;

	// String of inputValue
	string input = "";

	map->printMap();

	bool stopEditingMap = false;

	// Outer loop to continue allowing the user to edit the selected map.
	do {
		cout << "*** Editing map" << mapNumber << "\\" << mapName << " ***\n";
		// Input for the row
		int rowsInMap = map->getRows();
		int row = inputRowIndexToEdit(rowsInMap);

		// Input for column
		int columnsInMap = map->getColumns();
		int column = inputColumnIndexToEdit(columnsInMap);

		// Input for char
		string inputObject = inputCharObject(row, column);

		// Edit the cell if it is not empty
		if (!map->isOccupied(row, column)) {
			map->fillCell(row, column, inputObject);

			cout << "Result: \n";
			map->printMap();
		}
		else {
			cout << "An object already exists at that position.\n";
		}

		// Ask the user if they want to continue editing the map
		do {
			cout << "Enter 0 to cancel and return to the main menu \n";
			cout << "Enter 1 to continue editing the map \n";
			getline(cin, input);
			int option = -1;

			// Convert from string to number
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					return;
					//stopEditingMap = true;
					//isInputValid = true;
					//break;

				case 1:
					isInputValid = true;
					break;
				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!isInputValid);

	} while (!stopEditingMap);

}

void editCampaign(Campaign* campaign, vector<Map*>* maps)
{
	bool stopEditingCampaign = false;
	bool isInputValid = false;
	string input;

	// Outer loop to continue allowing the user to edit the selected campaign.
	do {
		cout << "*** Edit campaign ***\n";
		int option = -1;

		// Show menu to allow the user to edit the campaign.
		do {
			cout << "Enter 0 to cancel and return to the main menu \n";
			cout << "Enter 1 to add a map to the campaign \n";
			cout << "Enter 2 to remove a map from the campaign \n";
			getline(cin, input);
			option = -1;

			// Convert from string to number.
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					return;

				case 1:
					addMapToCampaign(campaign, maps);
					isInputValid = true;
					break;

				case 2:
					removeMapFromCampaign(campaign);
					isInputValid = true;
					break;
				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!isInputValid);

		isInputValid = false;
		// Ask the user if they want to continue editing the campaign
		do {
			cout << "Enter 0 to cancel and return to the main menu \n";
			cout << "Enter 1 to continue editing the campaign \n";
			getline(cin, input);
			option = -1;
			// This code converts from string to number safely.
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					stopEditingCampaign = true;
					isInputValid = true;
					break;

				case 1:
					isInputValid = true;
					break;
				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!isInputValid);

	} while (!stopEditingCampaign);
}

void addMapToCampaign(Campaign * campaign, vector<Map*>* maps)
{
	int mapCounter = -1;

	if (maps->size() == 0) {
		cout << "There are no available maps\n";
		return;
	}

	string input = "";
	int option;
	bool valid = false;
	bool stopAddingMaps = false;

	// Outer loop to continue allowing the user to add maps to the campaign
	do {
		cout << "*** Add maps to campaign ***\n";
		campaign->printMaps();

		cout << "***\n\n";
		cout << "Available maps\n";

		for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
			cout << "Map " << i << " : ";
			maps->at(i)->printMap();
			mapCounter++;
		}

		option = -1;
		do {
			cout << "Enter the number associated with the map to add it to the campaign: \n";
			getline(cin, input);
			stringstream myStream(input);
			if (myStream >> option) {
				if (option <= mapCounter) {
					valid = true;

					campaign->addMap(maps->at(option));

				}
				else {
					cout << "Invalid option, please try again.\n" << endl;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!valid);

		valid = false;
		// Ask the user if they want to continue editing the campaign
		do {
			cout << "Enter 0 to cancel and return to the previous menu \n";
			cout << "Enter 1 to continue adding maps to the campaign \n";
			getline(cin, input);
			option = -1;

			// This code converts from string to number safely.
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					return;

				case 1:
					valid = true;
					break;
				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!valid);

	} while (!stopAddingMaps);
}

void removeMapFromCampaign(Campaign * campaign)
{
	string input = "";
	int option;
	bool valid = false;
	int mapCounter = -1;
	vector<Map*>* maps = campaign->getMaps();

	// Outer loop to continue allowing the user to add maps to the campaign
	do {
		cout << "*** Remove maps from campaign ***\n";
		if (campaign->getMapsInCampaign() == 0) {
			cout << "The campaign does not contain any maps. Going back to the previous menu\n";
			return;
		}
		option = -1;
		do {

			cout << "***\n\n";
			cout << "Current maps in campaign " << campaign->getCampaignName() << "\n";

			for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
				cout << "Map " << i << " : ";
				maps->at(i)->printMap();
				mapCounter++;
			}

			cout << "Enter the number associated with the map to remove it to the campaign: \n";
			getline(cin, input);
			stringstream myStream(input);
			if (myStream >> option) {
				if (option <= mapCounter) {
					valid = true;

					campaign->removeMap(maps->at(option));

				}
				else {
					cout << "Invalid option, please try again.\n" << endl;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!valid);

		valid = false;
		// Ask the user if they want to continue editing the campaign
		do {
			cout << "Enter 0 to cancel and return to the previous menu \n";
			cout << "Enter 1 to continue removing maps from the campaign \n";
			getline(cin, input);
			option = -1;

			// This code converts from string to number safely.
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					return;

				case 1:
					valid = true;
					break;
				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		} while (!valid);

	} while (true);
}

void saveMaps(vector<Map*>* maps)
{
	cout << "*** Save maps ***\n";
	if (maps->empty()) {
		cout << "There are no maps to save\n";
		return;
	}

	string const folderName = "./maps/";

	for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
		// Make sure the map is valid before saving
		if (maps->at(i)->validatePath()) {
			string pathName = folderName + maps->at(i)->getMapName() + ".txt";
			//string pathName = "./maps/maptest.txt"; //works if folder exists
			ofstream mapFile(pathName);
			for (int row = 0; row < maps->at(i)->getRows(); row++)
			{
				for (int column = 0; column < maps->at(i)->getColumns(); column++)
				{
					if (mapFile.is_open())
					{
						mapFile << maps->at(i)->get(row, column) << ",";
					}
					else cout << "Unable to open file\n";
				}
				mapFile << "\n";
			}
			mapFile.close();
		}
		else {
			cout << "Unable to save map " << maps->at(i)->getMapName() << " because it is invalid.\n";
		}
	}

	cout << "Completed saving maps into the maps folder\n";
}

void saveCampaigns(vector<Campaign*>* campaigns)
{
	// Campaigns are only saved if all the maps within them are valid
	cout << "*** Save campaigns ***\n";
	if (campaigns->empty()) {
		cout << "There are no campaigns to save\n";
		return;
	}

	string const folderName = "./campaigns/";
	bool isCampaignValid = true;
	string campaignName = "";
	// Make sure all the maps belonging to a campaign are valid before saving the campaign.
	for (std::vector<Campaign*>::size_type c = 0; c != campaigns->size(); c++) {

		isCampaignValid = true;
		campaignName = campaigns->at(c)->getCampaignName();
		// Get vector of maps for campaign
		vector<Map*>* maps = campaigns->at(c)->getMaps();

		for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {

			// Make sure the map is valid before saving
			if (!(maps->at(i)->validatePath())) {
				isCampaignValid = false;
			}
		}

		if (isCampaignValid) {
			string pathName = folderName + campaigns->at(c)->getCampaignName() + ".txt";
			ofstream mapFile(pathName);

			for (std::vector<Map*>::size_type i = 0; i != maps->size(); i++) {
				for (int row = 0; row < maps->at(i)->getRows(); row++)
				{
					for (int column = 0; column < maps->at(i)->getColumns(); column++)
					{
						if (mapFile.is_open())
						{
							mapFile << maps->at(i)->get(row, column) << ",";
						}
						else cout << "Unable to open file\n";
					}
					mapFile << "\n";
				}
				mapFile << "\n*****\n";
			}
			mapFile.close();
			cout << "Saved campaign " << campaignName << endl;
		}
		else {
			cout << "Unable to save campaign " << campaignName << " because it contains maps which are invalid.\n";
		}
	}
}

void loadMaps(vector<Map*>* maps)
{
	cout << "***Load maps***\n";
	cout << "Be sure to add the .txt extension at the end of the filename\n";
	string name = inputName();
	string path = "./maps/" + name;

	try {
		MapDirector mapDirector;
		MapSaveBuilder* mapSaveBuilder = new MapSaveBuilder();
		mapDirector.setMapBuilder(mapSaveBuilder);
		mapDirector.constructMap(path);
		maps->push_back(new Map(*(mapSaveBuilder->getMap())));

		// Print the map
		cout << "\nMap created from " << name;
		maps->back()->printMap();
	}
	catch (...) {
		cout << "Loading map from file: " << name << " failed. Make sure the file exists.";
	}
}

// INPUT METHODS
//! Accepts user input for the number of columns to use in the new map.
int inputColumnsForNewMap() {
	int columns = 0;
	bool isInputValid = false;
	string input = "";

	do {
		cout << "Please enter the number of columns in the map (minimum 1):\n";
		getline(cin, input);

		// This code converts from string to number safely.
		stringstream myStream(input);
		if (myStream >> columns && columns > 0) {
			isInputValid = true;
		}
		else {
			cout << "Invalid number, please try again.\n" << endl;
		}
	} while (!isInputValid);
	return columns;
}

//! Accepts user input for the number of rows to use in the new map.
int inputRowsForNewMap() {
	int rows = 0;
	bool isInputValid = false;
	string input = "";

	// Input for for rows
	do {
		cout << "Please enter the number of rows in the map (minimum 1):\n";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> rows && rows > 0) {
			isInputValid = true;
		}
		else {
			cout << "Invalid number, please try again.\n" << endl;
		}
	} while (!isInputValid);
	return rows;
}

//! Accepts the row the index the user wishes to edit in an existing map.
int inputRowIndexToEdit(int rowsInMap)
{
	int row = 0;
	bool isInputValid = false;

	// String of inputValue
	string input = "";

	// Input for the row
	do {
		cout << "Please enter the row you wish to edit: \n";
		getline(cin, input);

		stringstream myStream(input);
		if (myStream >> row && row >= 0 && row < rowsInMap) {
			isInputValid = true;
		}
		else {
			cout << "Invalid number, please try again.\n" << endl;
		}
	} while (!isInputValid);
	return row;
}

int inputColumnIndexToEdit(int columnsInMap)
{
	int column = 0;
	bool isInputValid = false;

	// String of inputValue
	string input = "";

	// Input for the column
	do {
		cout << "Please enter the column you wish to edit: \n";
		getline(cin, input);

		// This code converts from string to number safely.
		stringstream myStream(input);
		if (myStream >> column && column >= 0 && column < columnsInMap) {
			isInputValid = true;
		}
		else {
			cout << "Invalid number, please try again.\n" << endl;
		}
	} while (!isInputValid);
	return column;
}

//! Accepts the char object the user wishes to enter into a cell.
string inputCharObject(int row, int column)
{
	bool isInputValid = false;
	char inputObject;
	string input = "";
	do {
		inputObject = { 0 };
		cout << "What would you like to enter at position " << row << ", " << column << ": \n";
		cout << "Enter a blank space to insert an empty cell \n";
		cout << "Enter 's' to insert a starting cell \n";
		cout << "Enter 'e' to insert an ending cell \n";
		cout << "Enter 't' to insert a chest \n";
		cout << "Enter 'm' to insert a monster \n";
		cout << "Enter '|' (pipe/ shift + backslash) to insert a wall \n";
		getline(cin, input);

		if (input.length() == 1) {
			inputObject = input[0];
			// Use constants later on.
			if (inputObject == ' ' || inputObject == 's' || inputObject == 'e' || inputObject == 't' || inputObject == 'm' || inputObject == '|') {
				isInputValid = true;
			}
			else {
				cout << "Invalid input, please try again.\n" << endl;
			}
		}
		else {
			cout << "Invalid input, please try again.\n" << endl;
		}
	} while (!isInputValid);
	return input;
}

//! Accepts input to use as the name of the object being worked on (map, campaign, character)
string inputName()
{
	bool isInputValid = false;
	string input = "";
	string name = "";
	int option = -1;

	do {
		cout << "\n";
		cout << "Enter the name:\n";
		getline(cin, input);
		name = input;

		if (!name.empty()) {
			cout << "\n";
			cout << "You entered: " << input << "\n";
			cout << "Enter 0 to cancel\n";
			cout << "Enter 1 to confirm\n";

			getline(cin, input);
			stringstream myStream(input);
			if (myStream >> option) {
				switch (option) {
				case 0:
					cout << "\n\n";
					isInputValid = false;
					break;

				case 1:
					cout << "\n\n";
					isInputValid = true;
					break;

				default:
					cout << "Invalid option, please try again.\n" << endl;
					break;
				}
			}
			else {
				cout << "Invalid option, please try again.\n" << endl;
			}
		}
		else {
			cout << "Cannot enter an empty string. Please try again.\n";
		}
	} while (!isInputValid);
	return name;
}





//! Code that was written without knowledge of Connor's classes.
//! Next revision will be a combination of said classes with my own work
int playDriver() {
	// *********************************************************INITIALIZATION AND SELECTION OF MAP AND CHARACTER *********************************************************

	Campaign* campaign = nullptr;
	Character* chara = nullptr;

	std::cout << "------------------------------\n";

	CampaignListings* campaignChoiceOptions = new CampaignListings();
	CharacterListings* characterChoiceOptions = new CharacterListings();

	std::cout << "------------------------------\n";

	if (campaignChoiceOptions->getNumberOfOptions() == 0 && characterChoiceOptions->getNumberOfOptions() == 0) {
		std::cout << "No maps or characters\nGo make some.\n";
		getchar();
		return -1;
	}
	else if (campaignChoiceOptions->getNumberOfOptions() == 0 || characterChoiceOptions->getNumberOfOptions() == 0) {
		std::cout << "No maps xor characters\nGo make some.\n";
		getchar();
		return -2;
	}

	bool repeat = true;
	while (repeat) {

		campaignChoiceOptions->displayMaps();
		campaign = campaignChoiceOptions->acceptInput4Map();
		MapObserver* mo1 = new MapObserver(campaign->getMap(0));
		std::cout << mo1->printMap() << "\n";

		characterChoiceOptions->displayCharacters();
		chara = characterChoiceOptions->acceptInput4Character();
		std::cout << chara->toString();
		//Map pointer has not been set yet

		std::cout << "\nYou're fine with this, right ?\nGive a 1 if yes and a 0 if no\n";
		char confirmation[9001] = "";
		std::cin >> confirmation;

		if (strcmp("0", confirmation) == 0) {
			std::cout << "\nWe'll do it again then...\n";
			campaign->getMap(0)->detatch();
			delete mo1;
		}
		else if (strcmp("1", confirmation) == 0) {
			std::cout << "\nLets move on...\n";
			//Set the map pointer
			//chara->postInitialize(campaign->getMap(0));
			campaign->getMap(0)->detatch();
			delete mo1;
			repeat = false;
		}
		else
			std::cout << "What is a " << confirmation << " ?\n";
	}

	delete campaignChoiceOptions;
	delete characterChoiceOptions;
	// ******************************************************************************************************************








	// ********************************************************* START OF GAME LOOP AND GAME PLAY *********************************************************

	GameDriver gd(chara, campaign);


	// ********************************************************* *********************************************************


}


//! Driver that calls showMainMenuForMapAndCampaign to run the Map and Campaign editor
void runDriver()
{
	showMainMenuForMapAndCampaign();
}