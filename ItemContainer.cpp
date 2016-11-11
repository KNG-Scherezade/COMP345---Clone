#include "ItemContainer.h"
using namespace std;

ItemContainer::ItemContainer()
{
	itemList = vector<Item>();
}

ItemContainer::ItemContainer(vector<Item> items)
{
	itemList = items;
}


ItemContainer::~ItemContainer()
{
}

Item ItemContainer::getItem(int index)
{
	if (index < itemList.size())
		return itemList[index];
	else
		return Item();
}

void ItemContainer::removeItem(int index)
{
	if (index < itemList.size())
		itemList.erase(itemList.begin() + index);
}

void ItemContainer::addItem(Item item)
{	
	itemList.push_back(item);
}
