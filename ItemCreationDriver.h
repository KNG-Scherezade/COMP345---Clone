//!@file ItemCreationDriver.cpp
//!  @brief declaration of the item creating class for the TUI

//!  This class implements functions that prompts the user to create items and save/load
#pragma once
#include <string>
class ItemCreationDriver
{
public:
	//! Displays the item menu and accepts input to guide the item creation process
	void showItemMenu();

	//! Loads the item in the given file
	//! @param fileName name of file containing item to be loaded
	//! @return returns the loaded item
	Item loadItem(string fileName);

	//! Saves the given item in the given file
	//! @param item the item to be saved
	//! @param fileName name of file containing item to be loaded
	void saveItem(Item item, string fileName);

	//! Prompts the user to load an item, after the item is loaded successfully the user is prompted to edit the item
	void showLoadMenu();
private:
	//! Prompts the user to save an item
	void showSaveDialogue(Item item);
	//! Prompts the user to edit an item
	void showEditDialogue(Item item);
	//! Helper menu for prompting entry of fields with numerical values
	int enterNumber(std::string attribute);
	//! Helper menu for prompting entry of fields with names
	std::string enterName();
};