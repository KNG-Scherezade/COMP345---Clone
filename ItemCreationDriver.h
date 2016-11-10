#pragma once
#include <string>
class ItemCreationDriver
{
public:
	std::string enterName();
	int enterNumber(std::string attribute);
	void showItemMenu();
	Item loadItem(string fileName);
	void saveItem(Item item, string fileName);
	void showLoadMenu();
private:
	void showSaveDialogue(Item item);

};