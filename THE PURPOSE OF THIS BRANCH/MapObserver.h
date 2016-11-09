//! The chest is the container for findable items in the game. It can either be empty or full depending on weather or not it has been used.
//! The chest's contents are scaled by the character and the contents are displayed to the user.

//! This is an observer for the chest. It takes chest information and prints it out to the console.

//! Vanilla C++


#pragma once
#include "Observable.h"
#include "Map.h"
#include <iostream>

class MapObserver :	public Observer
{
public:
	MapObserver(Subject* subj);
	~MapObserver();

	void update();
	std::string printMap();
	std::string printNotifications();
};

