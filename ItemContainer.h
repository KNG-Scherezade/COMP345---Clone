#pragma once
#include "Item.h"
#include "Map.h"
#include "Observable.h"
#include <vector>

class Map;

class ItemContainer : public Subject
{
public:
	ItemContainer();
	ItemContainer(vector<Item*> items);
	ItemContainer(Map* map, int x, int y);
	ItemContainer(vector<Item*> items, Map* map, int x, int y);
	~ItemContainer();

	Item* getItem(int index);
	void removeItem(int index);
	void removeItem(Item* item);
	void addItem(Item* item);
	vector<Item*> getItems() { return itemList; }

	void setOpen(bool flag);

	bool getOpen();
	int * getPosition();
	Map* getMap() { return map; }

	void notify();
	void attach(Observer* obs);

	std::string type;
	void setItemLevels(int level);
private:
	vector<Item*> itemList;

	int chestState;
	int position[2];
	bool open;
	Map* map;
};

