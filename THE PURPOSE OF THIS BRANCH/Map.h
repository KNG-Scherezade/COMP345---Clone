//! The map is the container for all visible game information meaning it tells the user where things are such as enemies, obstacles or chests.
//! Everything has a movespeed and everything has information on terrain type of obstacle or empty.

//! In this expansion on Akash's design the character is given a position on the map and methods relavent to the observer class are added.
//! These are getters, setters, notify and attatch.
//! Expaned upon are methods to check if a certain square can be walked upon either as an entrance, empty or exit space.
//! Simillarly a method to check what kind of square is at a certain location.
//! A currently unused method to create all movable locations within the characters move rate.
//! it contains the position of chests and characters as well as their objects.

//! Currently vanilla C++ is in use.


#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include<time.h>
#include <stdlib.h>  

#include "Node.h"
#include "Observable.h"
#include "Character.h"
#include "Chest.h"
#include "ChestObserver.h"
using namespace std;

class Chest;
class Character;
class ChestObserver;

class Map : public Subject
{
public:
	Map();
	Map(int newRows, int newColumns);
	//~Map();

	bool validatePath();
	void fillCell(int row, int col, char obj);
	bool isFunctionallyOccupied(int col, int row);
	bool isOccupied(int row, int col);
	
	void createMoveSpaceVector(std::vector <std::vector<int>>* validSpaces, int initialPosition[], int moveRate);
	int checkStandingSpace(int col, int row);

	void initializeMap(); // This is now public for the main to start once observers are attatched
	void deleteMap();

	void setCurrentSquare(int clearState);
	void setCharacterPosition(int pos[]);
	void setCharacter(Character *chara);


	int getRows();
	int getColumns();
	char** getMap();
	Character* getCharacter();
	int getCurrentSquare();
	int* getCharacterPosition();
	int getCharacterLevel();

	std::vector<Chest*> getChests();
	Chest* getChestAtPosition(int x, int y);

	//Subject inheritence / observer methods
	void attach(Observer* obs);
	void notify();
	//From top level: 	std::vector<Observer*> listeners;

private:
	int rows;
	int columns;
	char **map;

	int characterPosition[2];
	Character* character;
	std::vector<Chest*> chests; 
	std::vector<ChestObserver*> chestObservers;
	int currentSquare;

	Node* findStart();
	Node* findEnd();
	bool findValidPath(Node* startPointer, Node* endPointer);
	int calculateNodeId(int row, int column);
	int calculateHeuristic(int row, int column, int endRow, int endColumn);

};

