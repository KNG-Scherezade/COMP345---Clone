#pragma once
#include "Item.h"
#include <vector>
class ItemContainer
{
public:
	ItemContainer();
	ItemContainer(vector<Item> items);
	~ItemContainer();
	Item getItem(int index);
	void removeItem(int index);
	void removeItem(Item item);
	void addItem(Item item);
	vector<Item> getItems() { return itemList; }
private:
	vector<Item> itemList;

};

