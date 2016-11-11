//! The map is the container for all visible game information meaning it tells the user where things are such as enemies, obstacles or chests.
//! Everything has a movespeed and everything has information on terrain type of obstacle or empty.


//! This is an observer for the chest. It takes map information and prints it out to the console.

//! Vanilla C++

#pragma once
#include "Observable.h"
#include "ItemContainer.h"
#include <iostream>
class ChestObserver : public Observer
{
public:
	ChestObserver(Subject* subj);
	~ChestObserver();

	void update();
	void printChestDetails();
};

