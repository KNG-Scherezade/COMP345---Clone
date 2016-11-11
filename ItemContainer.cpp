#include "ItemContainer.h"
using namespace std;

ItemContainer::ItemContainer()
{
	itemList = vector<Item*>();
}

ItemContainer::ItemContainer(vector<Item*> items)
{
	itemList = items;
}

ItemContainer::ItemContainer(Map* map, int x, int y)
{
	itemList = vector<Item*>();

	this->map = map;
	position[0] = x;
	position[1] = y;
}

ItemContainer::ItemContainer(vector<Item*> items, Map* map, int x, int y)
{
	itemList = items;

	this->map = map;
	position[0] = x;
	position[1] = y;
}


ItemContainer::~ItemContainer()
{
}

Item* ItemContainer::getItem(int index)
{
	if (index < itemList.size())
		return itemList[index];
	else
		return new Item();
}

void ItemContainer::removeItem(int index)
{
	if (index < itemList.size())
		itemList.erase(itemList.begin() + index);
}

void ItemContainer::addItem(Item* item)
{	
	itemList.push_back(item);
}


//! sets check for if object containing items is closed or not
void ItemContainer::setOpen(bool flag) {
	open = flag;
}


//! gets check for if chest is closed or not
bool ItemContainer::getOpen() {
	return open;
}

//! gets chest position in x and y
int * ItemContainer::getPosition() {
	return position;
}

//! generic observer functions done in super
void ItemContainer::notify() {
	for each(Observer* obs in listeners) {
		obs->update();
	}
}
void ItemContainer::attach(Observer* obs) {
	listeners.push_back(obs);
}
