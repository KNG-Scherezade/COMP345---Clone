//! The chest is the container for findable items in the game. It can either be empty or full depending on weather or not it has been used.
//! The chest's contents are scaled by the character and the contents are displayed to the user.

//! The chest needs to know the characters level in order to scale the items.
//! It is used in the map.

//! Vanilla C++

#pragma once
#include "Observable.h"
#include "Map.h"

class Map;

class Chest : public Subject
{
public:
	Chest(Map* map, int x, int y);
	~Chest();

	int getChestState();
	void updateChestState();
	
	void setOpen(bool flag);

	bool getOpen();
	int * getPosition();

	void notify();
	void attach(Observer* obs);
	

private:
	int chestState;
	int position[2];
	bool open;
	Map* map;
};

